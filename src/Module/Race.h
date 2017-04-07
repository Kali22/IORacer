#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Vehicle.h>
#include "HUD.h"
#include <Map.h>
#include <CheckPointManager.h>
#include <ContactListener.h>
#include <Module/Module.h>

class Race : public Module {
public:
    Race(sf::RenderWindow *win) :
            Module(win), world(b2Vec2(0.f, 0.f)), map(&world), vehicle(carParameters), hud(vehicle, map) {
        // Initialize game
        Initialize();
    };

    int run();

    Vehicle *getVehicle();

private:
    //sf::RenderWindow &window;
    Map map;
    b2World world;
    Vehicle vehicle;
    CarParameters carParameters;
    HUD hud;
    ContactListener contactListener;
    CheckPointManager *checkPointManager_;

    void Initialize();
};

using RacePtr = Race*;