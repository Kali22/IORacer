#pragma once

#include <Activity.h>
#include "../Events/Event.h"
#include <Vehicle.h>
#include <MapManager.h>

class Gameplay : public Activity {
public:
    Gameplay(std::string mapName, int laps);

    void SetFirstPlayer(VehiclePtr vehicle);

    void SetSecondPlayer(VehiclePtr vehicle);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void HandleKey(sf::Event::KeyEvent event);

    int laps_;
    std::string mapName_;

    VehiclePtr firstPlayer_;
    VehiclePtr secondPlayer_;
    ScenePtr scene_;

    ObjectManagerPtr objectManager_;
    MapManagerPtr mapManager_;

    b2World *world_;
};

using GameplayPtr = std::shared_ptr<Gameplay>;

