#include "Splash.h"

#include <ActivityManager.h>

Splash::Splash() : Activity("splash") {}

void Splash::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void Splash::Init() {
    std::cerr << "Splash initialized!" << std::endl;
    UIBoxPtr splash = userInterface_->CreateBox("splash_screen", centeredFullScreen);
    splash->SetBackgroundTexture("splash");
}

void Splash::End() {}

void Splash::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        sf::Event sfmlEvent = event.GetSFMLEvent();
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(sfmlEvent.key);
        }
    } else if (event.GetType() == UI_EVENT) {
        if (event.GetUIEventType() == UI_EVENT_CLICK) {
            activityManager_->SetAsActive("player_selector");
            activityManager_->RemoveActivity("splash");
        }
    }
}

void Splash::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        activityManager_->End();
    }

    if (event.code == sf::Keyboard::Space) {
        activityManager_->SetAsActive("player_selector");
        activityManager_->RemoveActivity("splash");
    }
}
