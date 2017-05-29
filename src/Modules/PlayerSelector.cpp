#include "PlayerSelector.h"
#include <ActivityManager.h>
#include <NewRace.h>
#include <NewPlayer.h>

PlayerSelector::PlayerSelector(SelectorType type) :
        Activity("player_selector"),
        player_(0),
        type_(type) {
}

void PlayerSelector::Init() {
    playersList_ = activityManager_->GetPlayerManager()->GetPlayersList();
    if (type_ == SECOND_PLAYER) {
        std::string playerName = activityManager_->GetPlayerManager()->GetActivePlayer()->GetName();
        playersList_.erase(std::remove(playersList_.begin(), playersList_.end(), playerName), playersList_.end());
    }
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "Choose player", 70, sf::FloatRect(0.5, 0.075, 1, 0.1));
    SetTitleStyle(title);
    if (!playersList_.empty()) {
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
    sf::FloatRect new_player_pos = playersList_.empty() ?
                                   sf::FloatRect(0.5, 0.5, 0.2, 0.1) : sf::FloatRect(0.25, 0.8, 0.2, 0.1);
    UITextBoxPtr new_player = userInterface_->CreateTextBox("new_player", "New Player", 50, new_player_pos);
    SetButtonStyle(new_player);

}

void PlayerSelector::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
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
    } else if (event.GetType() == UI_EVENT) {
        if (event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "next") {
                if (player_ + 1 < playersList_.size())
                    player_++;
            }
            if (event.GetUIElement() == "prev") {
                if (player_ > 0)
                    player_--;
            }
            if (event.GetUIElement() == "select") {
                if (type_ == FIRST_PLAYER) {
                    activityManager_->GetPlayerManager()->SetActivePlayer(playersList_[player_]);
                    activityManager_->SetAsActive("main_menu");
                } else {
                    activityManager_->GetPlayerManager()->SetSecondPlayer(playersList_[player_]);
                    NewRacePtr newRace = std::make_shared<NewRace>(MULTI_PLAYER);
                    activityManager_->AddActivity(newRace);
                    activityManager_->SetAsActive("new_race");
                }
            }
            if (event.GetUIElement() == "new_player") {
                NewPlayerPtr newPlayer = std::make_shared<NewPlayer>(type_);
                activityManager_->AddActivity(newPlayer);
                activityManager_->SetAsActive("new_player");
            }
        }
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
            activityManager_->RemoveActivity("player_selector");
        else
            activityManager_->SetAsActive("main_menu");
    }
}