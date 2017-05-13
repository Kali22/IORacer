#pragma once

#include <SFML/Graphics.hpp>
#include "Module.h"
#include <Button.h>
#include <Race.h>
#include <ButtonManager.h>

class Workshop : public Module {
public:
    Workshop(RenderWindowPtr window, RacePtr race);

    int Run();

private:
    RacePtr race_;
    ButtonManagerPtr buttonManager_;
    CarParametersPtr carParams_;
    ButtonPtr returnButton_;
    TextPtr maxSpeedText_, maxEnginePowerText_, steeringSpeedText_;
    TextPtr maxSpeedLabel_, maxEnginePowerLabel_, steeringSpeedLabel_;
    ButtonPtr plusMaxSpeed_, minusMaxSpeed_;
    ButtonPtr plusMaxEnginePower_, minusMaxEnginePower_;
    ButtonPtr plusSteeringSpeed_, minusSteeringSpeed_;

    void InitializeMaxSpeedControl(const sf::Vector2f &labelSize,
                                   float textSize,
                                   int posX, int posY);

    void InitializeMaxEnginePowerControl(const sf::Vector2f &labelSize,
                                         float textSize,
                                         int posX, int posY);

    void InitializeSteeringSpeedControl(const sf::Vector2f &labelSize,
                                        float textSize,
                                        int posX, int posY);

    void InitializeText(TextPtr &textPtr, std::string initText, int posX, int posY, float textSize);

    void InitializeMinus(ButtonPtr &button, int posX, int posY, float &value, TextPtr &text);

    void InitializePlus(ButtonPtr &button, int posX, int posY, float &value, TextPtr &text);

    void InitializeDiff(ButtonPtr &button, int posX, int posY, float &value,
                        TextPtr &text, std::string label, int diff);

    void InitializeReturnButton(const sf::Vector2f &gameButtonSize, int windowWidth, int windowHeight);

    bool HandleEvents();

    void Draw();

};

using WorkshopPtr = std::shared_ptr<Workshop>;
