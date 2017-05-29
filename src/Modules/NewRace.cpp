#include "NewRace.h"

#include <ActivityManager.h>
#include <Gameplay.h>

const int default_laps_number = 2;

NewRace::NewRace(RaceType type) : Activity("new_race"), type_(type), laps_(default_laps_number) {}

void NewRace::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "Setup your race", 50,
                                                       sf::FloatRect(0.5, 0.075, 1, 0.1));
    SetTitleStyle(title);
    UITextBoxPtr m0 = userInterface_->CreateTextBox("map_0", "map_0", 30, sf::FloatRect(0.5, 0.5, 0.2, 0.05));
    UITextBoxPtr m1 = userInterface_->CreateTextBox("map_1", "map_1", 30, sf::FloatRect(0.5, 0.6, 0.2, 0.05));
    SetButtonStyle(m0);
    SetButtonStyle(m1);
    UITextBoxPtr laps = userInterface_->CreateTextBox("laps", std::to_string(laps_), 30,
                                                      sf::FloatRect(0.5, 0.2, 0.1, 0.05));
    SetButtonStyle(laps);
    UITextBoxPtr plus = userInterface_->CreateTextBox("inc_lap", "+", 30, sf::FloatRect(0.6, 0.2, 0.05, 0.05));
    SetButtonStyle(plus);
    UITextBoxPtr minus = userInterface_->CreateTextBox("dec_lap", "-", 30, sf::FloatRect(0.4, 0.2, 0.05, 0.05));
    SetButtonStyle(minus);
}

void NewRace::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    Update();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void NewRace::Update() {
    UITextBoxPtr nameTextBox = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("laps"));
    nameTextBox->SetText(std::to_string(laps_));
}

void NewRace::End() {}

void NewRace::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        sf::Event sfmlEvent = event.GetSFMLEvent();
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(sfmlEvent.key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if (event.GetUIEventType() == UI_EVENT_CLICK) {
            if (event.GetUIElement() == "dec_lap")
                if (laps_ > 1) laps_--;
            if (event.GetUIElement() == "inc_lap")
                if (laps_ < 99) laps_++;
            if (event.GetUIElement() == "map_0")
                CreateRace("map_0");
            if (event.GetUIElement() == "map_1")
                CreateRace("map_1");
        }
    }
}


void NewRace::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        if (type_ == SINGLE_PLAYER)
            activityManager_->SetAsActive("main_menu");
        else
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
    GameplayPtr race = std::make_shared<Gameplay>(name, laps_);
    PlayerPtr firstPlayer = activityManager_->GetPlayerManager()
            ->GetActivePlayer();
    race->SetFirstPlayer(firstPlayer);
    if (type_ == MULTI_PLAYER) {
        PlayerPtr secondPlayer = activityManager_->GetPlayerManager()
                ->GetSecondPlayer();
        race->SetSecondPlayer(secondPlayer);
    }
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
