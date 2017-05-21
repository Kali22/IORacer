#pragma once


#include <RealVec.h>
#include <bits/stdc++.h>

class Trackable {
public:
    virtual RealVec GetPosition() const = 0;
};
