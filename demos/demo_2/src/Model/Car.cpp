//
// Created by bartek on 06.04.17.
//

#include "Car.h"

Car::Car() : maxSpeed_(100.0), acceleration_(50.0), turnSpeed_(10.0), maxTurnAngle_(60.0) {}

Car::Car(float maxSpeed, float acceleration, float turnSpeed, float maxTurnAngle) :
        maxSpeed_(maxSpeed), acceleration_(acceleration), turnSpeed_(turnSpeed), maxTurnAngle_(maxTurnAngle) {}