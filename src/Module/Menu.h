#pragma once

#include "Module.h"
#include "Workshop.h"
#include <Button.h>
#include <Race.h>

class Menu : public Module {
public:
    Menu(sf::RenderWindow *window, RacePtr race);

    int Run();

private:
    RacePtr race_;
    WorkshopPtr workshop_;
    ButtonPtr playButton_, workshopButton_, quitButton_;

};

using MenuPtr = std::shared_ptr<Menu>;
