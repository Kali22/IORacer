#pragma once


#include <memory>

class Scalable {
public:
    virtual void Rescale(float scale) = 0;
};

using ScalablePtr = std::shared_ptr<Scalable>;
