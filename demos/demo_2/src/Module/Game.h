#pragma once

#include <SFML/Graphics.hpp>
#include "Module.h"
#include <Button.h>
#include <Model/GameData.h>

class Game : public Module {
public:
    Game(sf::RenderWindow *window, GameDataPtr gameData);

    int run();

private:
    GameDataPtr gameData_;
};

using GamePtr = std::shared_ptr<Game>;
