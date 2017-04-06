//
// Created by bartek on 06.04.17.
//

#include "Car.h"

Car::Car() : maxSpeed(100.0), acceleration(50.0), turnSpeed(10.0), maxTurnAngle(60.0) {}

Car::Car(float maxSpeed, float acceleration, float turnSpeed, float maxTurnAngle) :
        maxSpeed(maxSpeed), acceleration(acceleration), turnSpeed(turnSpeed), maxTurnAngle(maxTurnAngle) {}