#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Vehicle.h>
#include <Tools/HUD.h>
#include <Tools/Map.h>
#include <CheckPointManager.h>
#include <Tools/ContactListener.h>

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

