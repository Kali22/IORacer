#include <NewPlayer.h>
#include <ActivityManager.h>
#include <NewRace.h>

NewPlayer::NewPlayer(SelectorTypeE type) : Activity("new_player"), type_(type) {}

void NewPlayer::Init() {
    SetBackgroundToMenu();
    SetTitle("Choose your name");
    UITextBoxPtr player = userInterface_->CreateTextBox("name", "", 80, sf::FloatRect(0.5, 0.4, 0.7, 0.15));
    SetTextBoxStyle(player);
    UITextBoxPtr new_player = userInterface_->CreateTextBox("new_player", "Create", 50,
                                                            sf::FloatRect(0.5, 0.8, 0.2, 0.1));
    SetButtonStyle(new_player);
}

void NewPlayer::Run() {
    RendererPtr renderer = activityManager_.lock()->GetRenderer();
    Update();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void NewPlayer::End() {}

void NewPlayer::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        HandleSFMLEvent(event);
    } else if (event.GetType() == UI_EVENT && event.GetUIEventType() == UI_EVENT_CLICK) {
        if (event.GetUIElement() == "new_player")
            CreatePlayer();
    }
}

void NewPlayer::HandleSFMLEvent(Event event) {
    sf::Event sfmlEvent = event.GetSFMLEvent();
    if (sfmlEvent.type == sf::Event::KeyPressed) {
        HandleKey(sfmlEvent.key);
    }
    if (sfmlEvent.type == sf::Event::TextEntered) {
        if (32 < sfmlEvent.text.unicode && sfmlEvent.text.unicode < 126) {
            player_ += static_cast<char>(sfmlEvent.text.unicode);
        }
    }
}

void NewPlayer::CreatePlayer() {
    if (!player_.empty()) {
        PlayerManagerPtr playerManager = activityManager_.lock()->GetPlayerManager();
        playerManager->CreateNewPlayer(player_);
        if (type_ == FIRST_PLAYER) {
            playerManager->SetActivePlayer(player_);
            activityManager_.lock()->SetAsActive("main_menu");
        } else {
            playerManager->SetSecondPlayer(player_);
            NewRacePtr newRace = std::make_shared<NewRace>(MULTI_PLAYER);
            activityManager_.lock()->AddActivity(newRace);
            activityManager_.lock()->SetAsActive("new_race");
        }
    }
}

void NewPlayer::Update() {
    UITextBoxPtr nameTextBox = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("name"));
    nameTextBox->SetText(player_.c_str());
}

void NewPlayer::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Return)
        CreatePlayer();
    if (event.code == sf::Keyboard::BackSpace) {
        if (!player_.empty())
            player_.pop_back();
    }
    if (event.code == sf::Keyboard::Escape) {
        activityManager_.lock()->SetAsActive("player_selector");
    }
}
