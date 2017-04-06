//
// Created by bartek on 06.04.17.
//

#include "GameData.h"

GameData::GameData(Car_ptr car) : car(car) {
    //load Maps & all shit
}

GameData::GameData() : car(std::make_shared<Car>(100.0, 30.0, 50.0, 25.0)) {}
