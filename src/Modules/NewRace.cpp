#include "../Managers/ActivityManager.h"
#include "NewRace.h"
#include "Gameplay.h"

NewRace::NewRace() : Activity("new_race"){

}

void NewRace::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", sf::FloatRect(0.5, 0.5, 1, 1));
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "Setup your race", 50, sf::FloatRect(0.5, 0.075, 1, 0.1));
    SetTitleStyle(title);
    UITextBoxPtr m0 = userInterface_->CreateTextBox("map_0", "map_0", 30, sf::FloatRect(0.5, 0.5, 0.2, 0.05));
    UITextBoxPtr m1 = userInterface_->CreateTextBox("map_1", "map_1", 30, sf::FloatRect(0.5, 0.6, 0.2, 0.05));
    SetButtonStyle(m0);
    SetButtonStyle(m1);
    UITextBoxPtr right = userInterface_->CreateTextBox("inc_lap", ">", 30, sf::FloatRect(0.55, 0.2, 0.05, 0.05));
    SetButtonStyle(right);
    UITextBoxPtr left = userInterface_->CreateTextBox("dec_lap", "<", 30, sf::FloatRect(0.45, 0.2, 0.05, 0.05));
    SetButtonStyle(left);
}

void NewRace::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void NewRace::End() {

}

void NewRace::EventAction(Event event) {
    if (event.type == SFML_EVENT) {
        switch (event.sfmlEvent.type) {
            case sf::Event::KeyPressed:
                HandleKey(event.sfmlEvent.key);
                break;

            default:
                break;
        }
    } else if (event.type == UI_EVENT) {
        if (event.uiType == UI_EVENT_CLICK) {
            if (event.uiElenemt == "map_0") /// @todo Solve hardcoded ids
                CreateRace("map_0");
            if (event.uiElenemt == "map_1")
                CreateRace("map_1");
        }
    }
}



void NewRace::HandleKey(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Escape) {
        activityManager_->SetAsActive("player_selector");
    }
}

void NewRace::SetTitleStyle(UITextBoxPtr textBox) {
    textBox->SetTextColor(sf::Color::White);
    textBox->SetTextColorHover(sf::Color::White);
    textBox->SetBackgroundColor(sf::Color(0x2B405Bff));
    textBox->SetBackgroundColorHover(sf::Color(0x2B405Bff));
    textBox->SetOutlineColor(sf::Color(0xE1F0FFff));
    textBox->SetOutlineColorHover(sf::Color(0xE1F0FFff));
    textBox->SetOutlineThickness(1.f);
}

void NewRace::CreateRace(std::string name) {
    GameplayPtr race = std::make_shared<Gameplay>(name, 6);
    race->SetFirstPlayer("jacek");
    race->SetSecondPlayer("placek");
    activityManager_->AddActivity(race);
    activityManager_->SetAsActive("race");
}

void NewRace::SetButtonStyle(UITextBoxPtr button) {
    button->SetBackgroundColor(sf::Color(0x1c7396ff));
    button->SetBackgroundColorHover(sf::Color(0xD5E6E0ff));
    button->SetOutlineColor(sf::Color(0xE1F0FFff));
    button->SetOutlineColorHover(sf::Color(0x60758Cff));
    button->SetTextColor(sf::Color(0xD5E6E0ff));
    button->SetTextColorHover(sf::Color(0x1c7396ff));
    button->SetOutlineThickness(3.f);
}