//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_MENU_H
#define DEMO_2_MENU_H

#include "Module.h"

class Menu : public Module{
public:
    Menu(sf::RenderWindow *window);
    int run();
};


#endif //DEMO_2_MENU_H
