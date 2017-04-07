#pragma once

#include "Module.h"
#include "Workshop.h"
#include "Game.h.depr"
#include <Button.h>

class Menu : public Module {
public:
    Menu(sf::RenderWindow *window);

    int run();

private:
    RacePtr race_;
    WorkshopPtr workshop_;
    ButtonPtr playButton_, workshopButton_, quitButton_;

};

using MenuPtr = std::shared_ptr<Menu>;
