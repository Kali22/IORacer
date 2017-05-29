#pragma once


#include <bits/stdc++.h>

/* All possible objects in game. */
class Vehicle;

class Wheel;

class CheckPoint;

using VehiclePtr = std::shared_ptr<Vehicle>;
using WheelPtr = std::shared_ptr<Wheel>;
using CheckPointPtr = std::shared_ptr<CheckPoint>;
