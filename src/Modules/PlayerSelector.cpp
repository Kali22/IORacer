#include "PlayerSelector.h"
#include <ActivityManager.h>
#include <Player.h>
#include <Workshop.h>
#include <CarComponentManager.h>
#include <ViewportConst.h>

PlayerSelector::PlayerSelector() : Activity("player_selector") {

}

void PlayerSelector::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr play = userInterface_->CreateTextBox("start_game", "Play", 50, sf::FloatRect(0.5, 0.2, 0.2, 0.1));
    UITextBoxPtr workshop = userInterface_->CreateTextBox("workshop", "Workshop", 50, sf::FloatRect(0.5, 0.4, 0.2, 0.1));
    UITextBoxPtr quit = userInterface_->CreateTextBox("quit_game", "Quit",
                                                      50, sf::FloatRect(0.5, 0.6, 0.2, 0.1));
    SetButtonStyle(play);
    SetButtonStyle(workshop);
    SetButtonStyle(quit);
}

void PlayerSelector::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
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
            if (event.GetUIElement() == "start_game")
                activityManager_->SetAsActive("new_race");
            if (event.GetUIElement() == "workshop") {
                activityManager_->SetAsActive("workshop");
            }
            if (event.GetUIElement() == "quit_game")
                activityManager_->RemoveActivity("player_selector");
        }
    }
}

void PlayerSelector::HandleKey(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Escape) {
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
