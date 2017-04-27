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

    void InitializePlayButton(int windowWidth, int windowHeight, const sf::Vector2f &menuButtonSize);

    void InitializeWorkshopButton(int windowWidth, int windowHeight, const sf::Vector2f &menuButtonSize);

    void InitializeQuitButton(int windowWidth, int windowHeight, const sf::Vector2f &menuButtonSize);

    void HandleEvent(bool &mouseClick);

    void ServeButtons(bool &mouseClick);

    void Draw();
};

using MenuPtr = std::shared_ptr<Menu>;
