#pragma once

#include <memory>

class Car {
public:
    float maxSpeed_;
    float acceleration_;
    float turnSpeed_;
    float maxTurnAngle_;

    Car();

    Car(float maxSpeed, float acceleration, float turnSpeed, float maxTurnAngle);
};

using CarPtr = std::shared_ptr<Car>;
