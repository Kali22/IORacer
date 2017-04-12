#include <fstream>
#include <iostream>
#include "ObjectManager.h"

ObjectManager::ObjectManager() {
}

void ObjectManager::draw(sf::RenderWindow *window) {
    for (auto& object : objects) {
        object->draw(window);
    }
}

void ObjectManager::LoadObjects(b2World *world, std::string map_name) {
    std::ifstream description;
    description.open("../../resource/maps/" + map_name + "/description");
    char type;
    float x, y, angle;
    while (description >> type >> x >> y >> angle) {
        switch (type) {
            case 'c':
                objects.push_back(std::make_shared<Box>(world, x, y, angle));
                break;
            default:
                std::cerr << "Invalid entity type" << std::endl;
        }
    }
}







