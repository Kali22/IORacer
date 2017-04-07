#pragma once

#include "GameData.h"
#include "Module.h"
#include "Workshop.h"
#include "Game.h"
#include <Button.h>

class Menu : public Module {
public:
    Menu(sf::RenderWindow *window, GameDataPtr gameData);

    int run();

private:
    GameDataPtr gameData_;
    GamePtr game_;
    WorkshopPtr workshop_;
    ButtonPtr playButton_, workshopButton_, quitButton_;

};

using MenuPtr = std::shared_ptr<Menu>;
