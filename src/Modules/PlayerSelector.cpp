#include <PlayerSelector.h>
#include <ActivityManager.h>
#include <NewRace.h>
#include <NewPlayer.h>

PlayerSelector::PlayerSelector(SelectorTypeE type) : Activity("player_selector"), player_(0), type_(type) {}

void PlayerSelector::Init() {
    UpdatePlayersList();
    SetBackgroundToMenu();
    SetTitle("Choose player");
    ShowPlayers();
    EmplaceNewPlayerControls();
}

void PlayerSelector::UpdatePlayersList() {
    playersList_ = activityManager_.lock()->GetPlayerManager()->GetPlayersList();
    if (type_ == SECOND_PLAYER) {
        std::string playerName = activityManager_.lock()->GetPlayerManager()->GetActivePlayer()->GetName();
        playersList_.erase(std::remove(playersList_.begin(), playersList_.end(), playerName), playersList_.end());
    }
}

void PlayerSelector::ShowPlayers() {
    if (playersList_.empty())
        return;
    UITextBoxPtr left = userInterface_->CreateTextBox("prev", "<", 50, sf::FloatRect(0.2, 0.4, 0.05, 0.05));
    SetButtonStyle(left);
    UITextBoxPtr right = userInterface_->CreateTextBox("next", ">", 50, sf::FloatRect(0.8, 0.4, 0.05, 0.05));
    SetButtonStyle(right);
    UITextBoxPtr player = userInterface_->CreateTextBox("name", playersList_[player_], 80,
                                                        sf::FloatRect(0.5, 0.4, 0.5, 0.1));
    SetTextBoxStyle(player);
    UITextBoxPtr select = userInterface_->CreateTextBox("select", "Select", 50, sf::FloatRect(0.75, 0.8, 0.2, 0.1));
    SetButtonStyle(select);
}

void PlayerSelector::EmplaceNewPlayerControls() {
    sf::FloatRect new_player_pos = playersList_.empty() ?
                                   sf::FloatRect(0.5, 0.5, 0.2, 0.1) : sf::FloatRect(0.25, 0.8, 0.2, 0.1);
    UITextBoxPtr new_player = userInterface_->CreateTextBox("new_player", "New Player", 50, new_player_pos);
    SetButtonStyle(new_player);
}

void PlayerSelector::Run() {
    RendererPtr renderer = activityManager_.lock()->GetRenderer();
    Update();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void PlayerSelector::End() {}

void PlayerSelector::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        if (event.GetSFMLEvent().type == sf::Event::KeyPressed) {
            HandleKey(event.GetSFMLEvent().key);
        }
    } else if (event.GetType() == UI_EVENT && event.GetUIEventType() == UI_EVENT_CLICK) {
        HandleUIEventClick(event);
    }
}

void PlayerSelector::HandleUIEventClick(Event event) {
    unsigned long size = playersList_.size();
    if (event.GetUIElement() == "next") {
        player_ = (player_ + 1) % size;
    } else if (event.GetUIElement() == "prev") {
        player_ = (player_ + size - 1) % size;
    }
    if (event.GetUIElement() == "select") {
        SelectPlayer();
    }
    if (event.GetUIElement() == "new_player") {
        NewPlayerPtr newPlayer = std::make_shared<NewPlayer>(type_);
        activityManager_.lock()->AddActivity(newPlayer);
        activityManager_.lock()->SetAsActive("new_player");
    }
}

void PlayerSelector::SelectPlayer() {
    if (type_ == FIRST_PLAYER) {
        activityManager_.lock()->GetPlayerManager()->SetActivePlayer(playersList_[player_]);
        activityManager_.lock()->SetAsActive("main_menu");
    } else {
        activityManager_.lock()->GetPlayerManager()->SetSecondPlayer(playersList_[player_]);
        NewRacePtr newRace = std::make_shared<NewRace>(MULTI_PLAYER);
        activityManager_.lock()->AddActivity(newRace);
        activityManager_.lock()->SetAsActive("new_race");
    }
}

void PlayerSelector::Update() {
    if (!playersList_.empty()) {
        UITextBoxPtr nameTextBox = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("name"));
        nameTextBox->SetText(playersList_[player_]);
    }
}

void PlayerSelector::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        if (type_ == FIRST_PLAYER)
            activityManager_.lock()->RemoveActivity("player_selector");
        else
            activityManager_.lock()->SetAsActive("main_menu");
    }
}
