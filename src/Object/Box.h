#pragma once

#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Object.h"

class Box : public Entity, public Object {
    b2Body *body;
    sf::Sprite sprite;

public:
    Box(b2World *world, int x, int y, int angle);
    void draw(sf::RenderWindow *window);
    int GetEntityType() const;
};