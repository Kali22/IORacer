#include <ActivityManager.h>
#include "Gameplay.h"

Gameplay::Gameplay(std::string mapName, int laps) : Activity("race"), laps_(laps), mapName_(mapName) {

}

void Gameplay::Init() {
    world_ = new b2World(b2Vec2(0, 0));
    objectManager_ = std::make_shared<ObjectManager>(activityManager_->GetTextureManager(), world_);
    mapManager_ = std::make_shared<MapManager>(activityManager_->GetTextureManager(), objectManager_);
    scene_ = std::make_shared<Scene>(mapManager_->CreateMap(mapName_));
    scene_->AddCamera(RealVec(0, 0), 100, 1);
}

void Gameplay::Run() {
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    renderer->RenderScene(scene_, VIEW_TYPE_SINGLE);
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void Gameplay::End() {
    free(world_);
}

void Gameplay::EventAction(Event event) {
    if (event.type == SFML_EVENT) {
        if (event.sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(event.sfmlEvent.key);
        }
    }

}

void Gameplay::HandleKey(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        activityManager_->RemoveActivity("race");
        activityManager_->SetAsActive("player_selector");
    }
}

void Gameplay::SetFirstPlayer(VehiclePtr vehicle) {

}

void Gameplay::SetSecondPlayer(VehiclePtr vehicle) {

}
