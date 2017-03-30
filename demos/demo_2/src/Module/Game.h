//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_GAME_H
#define DEMO_2_GAME_H

#include <SFML/Graphics.hpp>
#include "Module.h"
#include "../Entity/Button.h"

class Game : public Module {

public:
    Game(sf::RenderWindow *window);

    int run();
};


#endif //DEMO_2_GAME_H
