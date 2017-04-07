//
// Created by bartek on 06.04.17.
//

#include "GameData.h"

GameData::GameData(CarPtr car) : car_(car) {
    //load Maps & all
}

GameData::GameData() : car_(std::make_shared<Car>(100.0, 30.0, 50.0, 25.0)) {}
