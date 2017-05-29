#pragma once


#include <SFML/System.hpp>

class Rotatable {
public:
    virtual void Rotate(float angle) = 0;

    virtual void SetRotation(float absoluteAngle) = 0;
};
