#pragma once

#include "Car.h"

class GameData {
public:
    CarPtr car_;

    //Maps
    GameData();

    GameData(CarPtr car);
};

using GameDataPtr = std::shared_ptr<GameData>;

