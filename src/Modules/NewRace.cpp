#include <ActivityManager.h>
#include "NewRace.h"

NewRace::NewRace() : Activity("new_race"){

}

void NewRace::Init() {
    UIBoxPtr back = userInterface_->CreateBox("background", sf::FloatRect(0.5, 0.5, 1, 1));
    back->SetBackgroundTexture("menu_back");
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "Setup your race", 50, sf::FloatRect(0.5, 0.075, 1, 0.1));
    SetTitleStyle(title);
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
    if (event.type == SFML_EVENT){
        switch (event.sfmlEvent.type) {
            case sf::Event::KeyPressed:
                HandleKey(event.sfmlEvent.key);
                break;

            default:
                break;
        }
    }
}



void NewRace::HandleKey(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Escape) {
        activityManager_->SetAsActive("player_selector");
    } else if(event.code == sf::Keyboard::Space) {
        CreateRace();
        activityManager_->SetAsActive("race");
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

void NewRace::CreateRace() {

}
