#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Vehicle.h>
#include "Tools/HUD.h"
#include <Tools/Map.h>
#include <CheckPointManager.h>
#include <Tools/ContactListener.h>
#include <Module/Module.h>

class Race : public Module {
public:
    Race(sf::RenderWindow *window, b2World *world, MapPtr map, HUDPtr hud, CheckPointManagerPtr checkPointManager) :
            Module(window), world_(world), map_(map), hud_(hud), checkPointManager_(checkPointManager) {};

    int Run();

    VehiclePtr GetVehicle();

    void Reset();

    void Initialize(VehiclePtr vehicle);

private:
    MapPtr map_;
    b2World *world_;
    VehiclePtr vehicle_;
    HUDPtr hud_;
    ContactListener contactListener_;
    CheckPointManagerPtr checkPointManager_;

    void HandleKeyboard(sf::Event::KeyEvent Event, int *state, int type);
};

using RacePtr = std::shared_ptr<Race>;
