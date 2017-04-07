#pragma once

#include <SFML/Graphics.hpp>
#include <Drawable.h>
#include <Entity.h>


class Area : public Drawable {
public:
    virtual void SetCollisionUserData(Entity* entity) = 0;

    virtual void Draw(sf::RenderWindow *window) = 0;
};
