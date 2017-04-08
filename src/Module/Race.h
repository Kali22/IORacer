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
            Module(win) {
        // Initialize game
        Initialize();
    };

    int run();

    Vehicle *getVehicle();

private:
    //sf::RenderWindow &window;
    Map* map_;
    b2World* world_;
    Vehicle* vehicle_;
    CarParameters carParameters_;
    HUD* hud_;
    ContactListener contactListener_;
    CheckPointManager *checkPointManager_;

    void Initialize();
};

using RacePtr = Race*;