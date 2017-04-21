#include <fstream>
#include <iostream>
#include "ObjectManager.h"
#include "TruckTire.h"
#include "Box.h"

ObjectManager::ObjectManager() {
}

void ObjectManager::draw(sf::RenderWindow *window) {
    for (auto& object : objects) {
        object->draw(window);
    }
}

void ObjectManager::LoadObjects(b2World *world, std::string map_name, float scale) {
    std::ifstream description;
    description.open("../resource/maps/" + map_name + "/description");
    if (!description.is_open()) {
        std::cerr << "Opening description failed" << std::endl;
    }
    char type;
    float x, y, angle;
    while (description >> type >> x >> y >> angle) {
        switch (type) {
            case 'b':
                objects.push_back(std::make_shared<Box>(world, x, y, angle, scale));
                break;
            case 't':
                objects.push_back(std::make_shared<TruckTire>(world, x, y, angle, scale));
                break;
            default:
                std::cerr << "Invalid entity type" << std::endl;
        }
    }
}