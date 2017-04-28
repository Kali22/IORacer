//
// Created by jacek on 20.04.17.
//
#pragma once

#include <SFML/System.hpp>
#include <Entity/Drawable.h>

class Movable : public Drawable {
public:
    virtual void SetPosition(const sf::Vector2f &pos) = 0;

    virtual void SetPosition(float x, float y) = 0;

    virtual void Move(const sf::Vector2f &dr) = 0;

    virtual void Move(float dx, float dy) = 0;
};

using MovablePtr = std::shared_ptr<Movable>;
