#include "MainMenu.h"
#include <ActivityManager.h>
#include <Workshop.h>
#include <CarComponentManager.h>
#include <ViewportConst.h>
#include <PlayerManager.h>
#include <NewRace.h>
#include <PlayerSelector.h>

MainMenu::MainMenu() : Activity("main_menu") {

}

void MainMenu::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr single = userInterface_->CreateTextBox("single_player", "Single Player", 50, sf::FloatRect(0.5, 0.2, 0.2, 0.1));
    UITextBoxPtr multi = userInterface_->CreateTextBox("multi_player", "Multi Player", 50, sf::FloatRect(0.5, 0.4, 0.2, 0.1));
    UITextBoxPtr workshop = userInterface_->CreateTextBox("workshop", "Workshop", 50, sf::FloatRect(0.5, 0.6, 0.2, 0.1));
    UITextBoxPtr quit = userInterface_->CreateTextBox("quit_game", "Quit",
                                                      50, sf::FloatRect(0.5, 0.8, 0.2, 0.1));
    SetButtonStyle(single);
    SetButtonStyle(multi);
    SetButtonStyle(workshop);
    SetButtonStyle(quit);
}

void MainMenu::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void MainMenu::End() {

}

void MainMenu::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        if (event.GetSFMLEvent().type == sf::Event::KeyPressed) {
                HandleKey(event.GetSFMLEvent().key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if(event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "single_player") {
                NewRacePtr newRace = std::make_shared<NewRace>(SINGLE_PLAYER);
                activityManager_->AddActivity(newRace);
                activityManager_->SetAsActive("new_race");
            }
            if (event.GetUIElement() == "multi_player") {
                PlayerSelectorPtr selector = std::make_shared<PlayerSelector>(SECOND_PLAYER);
                activityManager_->AddActivity(selector);
                activityManager_->SetAsActive("player_selector");
            }
            if (event.GetUIElement() == "workshop") {
                WorkshopPtr workshop = std::make_shared<Workshop>();
                activityManager_->AddActivity(workshop);
                activityManager_->SetAsActive("workshop");
            }
            if (event.GetUIElement() == "quit_game")
                activityManager_->RemoveActivity("main_menu");
        }
    }
}

void MainMenu::HandleKey(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Escape) {
        activityManager_->RemoveActivity("main_menu");
    }
}

void MainMenu::SetButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(sf::Color(0x1c7396ff));
    button->SetBackgroundColorHover(sf::Color(0xD5E6E0ff));
    button->SetOutlineColor(sf::Color(0xE1F0FFff));
    button->SetOutlineColorHover(sf::Color(0x60758Cff));
    button->SetTextColor(sf::Color(0xD5E6E0ff));
    button->SetTextColorHover(sf::Color(0x1c7396ff));
    button->SetOutlineThickness(3.f);
}
