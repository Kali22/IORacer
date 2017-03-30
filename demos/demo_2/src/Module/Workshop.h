//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_WORKSHOP_H
#define DEMO_2_WORKSHOP_H


#include <SFML/Graphics.hpp>
#include "Module.h"
#include "../Entity/Button.h"


class Workshop : public Module {
public:
    Workshop(sf::RenderWindow *window);

    int run();
};


#endif //DEMO_2_WORKSHOP_H
