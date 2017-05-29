#pragma once


#include <RealVec.h>

class Trackable {
public:
    virtual RealVec GetPosition() const = 0;
};
