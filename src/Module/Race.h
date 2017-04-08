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
    Race(sf::RenderWindow *win, b2World* world, Map* map, HUD* hud,
         CheckPointManager* checkPointManager) :
            Module(win), world_(world), map_(map), hud_(hud),
            checkPointManager_(checkPointManager) {
    };

    int run();

    Vehicle *getVehicle();

    void Initialize(Vehicle* vehicle);
private:
    //sf::RenderWindow &window;
    Map* map_;
    b2World* world_;
    HUD* hud_;
    CheckPointManager *checkPointManager_;
    Vehicle* vehicle_;

    ContactListener contactListener_;
};

using RacePtr = Race*;