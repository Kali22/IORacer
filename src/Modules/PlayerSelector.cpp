#include "PlayerSelector.h"
#include <ActivityManager.h>
#include <PlayerManager.h>
#include <Player.h>

#include <ViewportConst.h>

extern PlayerManagerPtr playerManager;

PlayerSelector::PlayerSelector() : Activity("player_selector"), player_(0), playersList_(playerManager->GetPlayersList()) {
}

void PlayerSelector::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    if (!playersList_.empty()) {
        UITextBoxPtr left = userInterface_->CreateTextBox("prev", "<", 50, sf::FloatRect(0.2, 0.4, 0.05, 0.05));
        SetButtonStyle(left);
        UITextBoxPtr right = userInterface_->CreateTextBox("next", ">", 50, sf::FloatRect(0.8, 0.4, 0.05, 0.05));
        SetButtonStyle(right);
        UITextBoxPtr player = userInterface_->CreateTextBox("name", playersList_[player_], 80, sf::FloatRect(0.5, 0.4, 0.5, 0.1));
        SetTextBoxStyle(player);
        UITextBoxPtr select = userInterface_->CreateTextBox("select", "Select", 50, sf::FloatRect(0.75, 0.8, 0.2, 0.1));
        SetButtonStyle(select);
    }
    sf::FloatRect new_player_pos = playersList_.empty() ? sf::FloatRect(0.5, 0.5, 0.2, 0.1) : sf::FloatRect(0.25, 0.8, 0.2, 0.1);
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

void PlayerSelector::End() {
}

void PlayerSelector::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        if (event.GetSFMLEvent().type == sf::Event::KeyPressed) {
            HandleKey(event.GetSFMLEvent().key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if(event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "next") {
                if (player_ + 1 < playersList_.size())
                    player_++;
            }
            if (event.GetUIElement() == "prev") {
                if (player_ > 0)
                    player_--;
            }
            if (event.GetUIElement() == "select") {
                playerManager->SetActivePlayer(playersList_[player_]);
                activityManager_->SetAsActive("main_menu");
            }
            if (event.GetUIElement() == "new_player")
                activityManager_->SetAsActive("new_player");
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
        activityManager_->RemoveActivity("player_selector");
    }
}

void PlayerSelector::SetButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(sf::Color(0x1c7396ff));
    button->SetBackgroundColorHover(sf::Color(0xD5E6E0ff));
    button->SetOutlineColor(sf::Color(0xE1F0FFff));
    button->SetOutlineColorHover(sf::Color(0x60758Cff));
    button->SetTextColor(sf::Color(0xD5E6E0ff));
    button->SetTextColorHover(sf::Color(0x1c7396ff));
    button->SetOutlineThickness(3.f);
}

void PlayerSelector::SetTextBoxStyle(UITextBoxPtr textBox) {
    textBox->SetBackgroundColor(sf::Color(0x1c7396ff));
    textBox->SetBackgroundColorHover(sf::Color(0x1c7396ff));
    textBox->SetOutlineColor(sf::Color(0xE1F0FFff));
    textBox->SetOutlineColorHover(sf::Color(0xE1F0FFff));
    textBox->SetTextColor(sf::Color(0xD5E6E0ff));
    textBox->SetTextColorHover(sf::Color(0xD5E6E0ff));
    textBox->SetOutlineThickness(3.f);
}





