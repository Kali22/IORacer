#pragma once


#include <RealVec.h>
#include <bits/stdc++.h>

class Trackable {
public:
    virtual RealVec GetPosition() const = 0;
};

using TrackablePtr = std::shared_ptr<Trackable>;
