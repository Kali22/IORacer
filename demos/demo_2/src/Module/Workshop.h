#pragma once

#include <SFML/Graphics.hpp>
#include <GameData.h>
#include "Module.h"
#include <Button.h>


class Workshop : public Module {
public:
    Workshop(sf::RenderWindow *window, GameDataPtr gameData);

    int run();

private:
    GameDataPtr gameData_;
    ButtonPtr returnButton_;
    TextPtr maxSpeedText_, accelerationText_;
    ButtonPtr plusMaxSpeed_, minusMaxSpeed_;
    ButtonPtr plusAcceleration_, minusAcceleration_;
};

using WorkshopPtr = std::shared_ptr<Workshop>;
