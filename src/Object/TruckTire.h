#pragma once

#include <Tools/Entity.h>
#include "Object.h"

class TruckTire : public Entity, public Object {
public:
    TruckTire(b2World *world, int x, int y, int angle, float scale);
    void draw(sf::RenderWindow *window);
    int GetEntityType() const;
};