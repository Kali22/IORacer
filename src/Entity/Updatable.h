//
// Created by jacek on 20.04.17.
//

#pragma once

#include <bits/stdc++.h>

class Updatable {
public:
    virtual void Update() = 0;
};

using UpdatablePtr = std::shared_ptr<Updatable>;
