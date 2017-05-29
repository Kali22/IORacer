#pragma once


#include <Drawable.h>
#include <memory>
#include <SFML/System.hpp>

class Movable {
public:
    virtual void Draw(RenderWindowPtr window) const = 0; // TODO in two interfaces

    virtual void SetPosition(const sf::Vector2f &pos) = 0;

    virtual void SetPosition(float x, float y) = 0;

    virtual void Move(const sf::Vector2f &dr) = 0;

    virtual void Move(float offsetX, float offsetY) = 0;
};

using MovablePtr = std::shared_ptr<Movable>;
