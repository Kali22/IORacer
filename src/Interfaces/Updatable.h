#pragma once


#include <memory>

class Updatable {
public:
    virtual void Update() = 0;
};

using UpdatablePtr = std::shared_ptr<Updatable>;
