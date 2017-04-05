//
// Created by pawel on 30.03.17.
//

#ifndef RACE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Car.h>
#include <Map.h>
#include <CheckPointManager.h>
#include <ContactListener.h>

class Race {
private:
    sf::RenderWindow& window;
    Map map;
    b2World world;
    Car car;
    ContactListener contactListener;
    CheckPointManager* checkPointManager_;

    void Initialize();
public:
    Race(sf::RenderWindow& win) : window(win), world(b2Vec2(0.f, 0.f)), map(world) { };
    void Run();
};

#endif //RACE_H
