//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_GAME_H
#define DEMO_2_GAME_H

#include <SFML/Graphics.hpp>
#include "Module.h"
#include <Button.h>
#include <Model/GameData.h>

class Game : public Module {
    GameData_ptr gameData;

public:
    Game(sf::RenderWindow *window, GameData_ptr gameData);

    int run();
};

typedef std::shared_ptr <Game> Game_ptr;

#endif //DEMO_2_GAME_H
