#pragma once

#include <SFML/Graphics.hpp>
#include "Module.h"
#include <Button.h>
#include <Race.h>


class Workshop : public Module {
public:
    Workshop(sf::RenderWindow *window, RacePtr race);

    int run();

private:
    RacePtr race_;
    CarParametersPtr carParams_;
    ButtonPtr returnButton_;
    TextPtr maxSpeedText_, accelerationText_;
    ButtonPtr plusMaxSpeed_, minusMaxSpeed_;
    ButtonPtr plusAcceleration_, minusAcceleration_;
};

using WorkshopPtr = std::shared_ptr<Workshop>;
