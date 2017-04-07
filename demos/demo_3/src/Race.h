#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Vehicle.h>
#include <HUD.h>
#include <Map.h>
#include <CheckPointManager.h>
#include <ContactListener.h>

class Race {
public:
    Race(sf::RenderWindow* win, b2World* world, Map* map, Vehicle* vehicle,
         HUD* hud, CheckPointManager* checkPointManager);
    void Run();
private:
    sf::RenderWindow* window_;
    Map* map_;
    b2World* world_;
    Vehicle* vehicle_;
    HUD* hud_;
    ContactListener contactListener;
    CheckPointManager* checkPointManager_;

    void Initialize();
};

