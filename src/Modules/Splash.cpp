#include "Splash.h"
#include "../Managers/ActivityManager.h"
#include "../Events/Event.h"

Splash::Splash() : Activity("splash") {

}

void Splash::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void Splash::Init() {
    fprintf(stderr, "Splash initialized!\n");
    UIBoxPtr splash = userInterface_->CreateBox("splash_screen", sf::FloatRect(0.5, 0.5, 1, 1));
    splash->SetBackgroundTexture("splash");
}

void Splash::End() {

}

void Splash::EventAction(Event event) {
    if (event.type == SFML_EVENT) {
        switch (event.sfmlEvent.type) {
            case sf::Event::KeyPressed:
                HandleKey(event.sfmlEvent.key);
                break;

            default:
                break;
        }
    } else if (event.type == UI_EVENT) {
        switch (event.uiType) {
            case UI_EVENT_CLICK:
                activityManager_->SetAsActive("player_selector");
                activityManager_->RemoveActivity("splash");
                break;
            default:
                break;
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
