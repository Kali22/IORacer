#pragma once

#include <Box2D.h>

struct RectangleParams {
    b2Vec2 b2Pos;
    b2Vec2 b2Size;
    float b2Angle;

    sf::Vector2f sfmlPos;
    sf::Vector2f sfmlSize;
    float sfmlAngle;
};
