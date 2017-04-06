//
// Created by bartek on 06.04.17.
//

#ifndef DEMO_2_GAMEPLAY_H
#define DEMO_2_GAMEPLAY_H

#include "Car.h"

class GameData {
public:
    Car_ptr car;

    //Maps
    GameData();

    GameData(Car_ptr car);
};

typedef std::shared_ptr <GameData> GameData_ptr;

#endif //DEMO_2_GAMEPLAY_H
