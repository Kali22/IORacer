//
// Created by bartek on 06.04.17.
//

#ifndef DEMO_2_CAR_H
#define DEMO_2_CAR_H

#include <memory>

class Car {
public:
    float maxSpeed;
    float acceleration;
    float turnSpeed;
    float maxTurnAngle;

    Car();

    Car(float maxSpeed, float acceleration, float turnSpeed, float maxTurnAngle);
};

typedef std::shared_ptr <Car> Car_ptr;

#endif //DEMO_2_CAR_H
