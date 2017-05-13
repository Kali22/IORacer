#pragma once


#include <bits/shared_ptr.h>

class Scalable {
public:
    virtual void Rescale(float scale) = 0;
};

using ScalablePtr = std::shared_ptr<Scalable>;