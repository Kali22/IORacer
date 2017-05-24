#pragma once

#include <string>
#include <bits/stdc++.h>
#include <Vehicle.h>

/// TODO add achivements
class Player {
public:
    Player(const std::string& name, VehiclePtr vehicle);

    std::string GetName() const;

    VehiclePtr GetVehicle() const;
private:
    std::string name_;
    VehiclePtr vehicle_;
};

using PlayerPtr = std::shared_ptr<Player>;
