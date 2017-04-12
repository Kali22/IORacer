#pragma once

#include <string>
#include <Box2D.h>
#include <memory.h>
#include "Box.h"
#include "Object.h"

class ObjectManager {
    std::vector<std::shared_ptr<Object> > objects;
public:
    ObjectManager();
    void LoadObjects(b2World *world, std::string map_name);
    void draw(sf::RenderWindow *window);

};