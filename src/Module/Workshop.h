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
    TextPtr maxSpeedText_, maxEnginePowerText_, steeringSpeedText_;
    TextPtr maxSpeedLabel_, maxEnginePowerLabel_, steeringSpeedLabel_;
    ButtonPtr plusMaxSpeed_, minusMaxSpeed_;
    ButtonPtr plusMaxEnginePower_, minusMaxEnginePower_;
    ButtonPtr plusSteeringSpeed_, minusSteeringSpeed_;

    void initMaxSpeedControl(
            const sf::Vector2f &statsButtonSize, const sf::Vector2f &labelSize, float textSize, int posX, int posY);

    void initMaxEnginePowerControl(const sf::Vector2f &statsButtonSize, const sf::Vector2f &labelSize, float textSize,
                                   int posX, int posY);

    void initSteeringSpeedControl(const sf::Vector2f &statsButtonSize, const sf::Vector2f &labelSize, float textSize,
                                  int posX, int posY);
};

using WorkshopPtr = std::shared_ptr<Workshop>;
