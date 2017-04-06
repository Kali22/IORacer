//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_WORKSHOP_H
#define DEMO_2_WORKSHOP_H


#include <SFML/Graphics.hpp>
#include <GameData.h>
#include "Module.h"
#include <Button.h>


class Workshop : public Module {

    GameData_ptr gameData;
    Button_ptr returnButton;
    Text_ptr maxSpeedText, accelerationText;
    Button_ptr plusMaxSpeed, minusMaxSpeed;
    Button_ptr plusAcceleration, minusAcceleration;


public:
    Workshop(sf::RenderWindow *window, GameData_ptr gameData);

    int run();
};

using Workshop_ptr = std::shared_ptr<Workshop>;

#endif //DEMO_2_WORKSHOP_H
