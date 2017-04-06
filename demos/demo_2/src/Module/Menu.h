//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_MENU_H
#define DEMO_2_MENU_H

#include "GameData.h"
#include "Module.h"
#include "Workshop.h"
#include "Game.h"
#include <Button.h>

class Menu : public Module {
    GameData_ptr gameData;
    Game_ptr game;
    Workshop_ptr workshop;
    Button_ptr playButton, workshopButton, quitButton;

public:
    Menu(sf::RenderWindow *window, GameData_ptr gameData);

    int run();
};

using Menu_ptr = std::shared_ptr<Menu>;

#endif //DEMO_2_MENU_H
