#pragma once

#include <Box2D.h>
#include <SFML/Graphics.hpp>

class Object {
protected:
    float scale_;
    b2Body *body_;
    sf::Sprite sprite_;

public:
    virtual void draw(sf::RenderWindow *window) = 0;
};