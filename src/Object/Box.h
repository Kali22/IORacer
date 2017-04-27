#pragma once

#include "Entity.h"
#include "Object.h"

class Box : public Entity, public Object {
public:
    Box(b2World *world, int x, int y, int angle, float scale);

    void draw(sf::RenderWindow *window);

    int GetEntityType() const;

private:
    const float boxSize_ = 48.f;

    void InitializeBody(b2World *world, int x, int y, int angle);

    void InitializeFixture();
};