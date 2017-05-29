#include "NewPlayer.h"
#include <ActivityManager.h>
#include <PlayerManager.h>
#include <ViewportConst.h>
#include <NewRace.h>

NewPlayer::NewPlayer(SelectorType type) : Activity("new_player"), type_(type) {
}

void NewPlayer::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "", 70, sf::FloatRect(0.5, 0.075, 1, 0.1));
    SetTitleStyle(title);
    UITextBoxPtr player = userInterface_->CreateTextBox("name", "", 80, sf::FloatRect(0.5, 0.4, 0.7, 0.15));
    SetTextBoxStyle(player);
    UITextBoxPtr new_player = userInterface_->CreateTextBox("new_player", "Create", 50, sf::FloatRect(0.5, 0.8, 0.2, 0.1));
    SetButtonStyle(new_player);
}

void NewPlayer::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    Update();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void NewPlayer::End() {

}

void NewPlayer::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        sf::Event sfmlEvent = event.GetSFMLEvent();
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(sfmlEvent.key);
        }
        if (sfmlEvent.type == sf::Event::TextEntered) {
            if (32 < sfmlEvent.text.unicode && sfmlEvent.text.unicode < 126) {
                player_ += static_cast<char>(sfmlEvent.text.unicode);
            }
        }
    } else if (event.GetType() == UI_EVENT) {
        if(event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "new_player")
                CreatePlayer();
        }
    }
}

void NewPlayer::CreatePlayer() {
    if (!player_.empty()) {
        PlayerManagerPtr playerManager = activityManager_->GetPlayerManager();
        playerManager->CreateNewPlayer(player_);
        if (type_ == FIRST_PLAYER) {
            playerManager->SetActivePlayer(player_);
            activityManager_->SetAsActive("main_menu");
        }
        else {
            playerManager->SetSecondPlayer(player_);
            NewRacePtr newRace = std::make_shared<NewRace>(MULTI_PLAYER);
            activityManager_->AddActivity(newRace);
            activityManager_->SetAsActive("new_race");
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
        activityManager_->SetAsActive("player_selector");
    }
}
