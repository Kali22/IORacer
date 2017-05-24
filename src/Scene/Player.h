#pragma once

#include <string>
#include <bits/stdc++.h>
#include <Vehicle.h>

/// TODO add achivements
class Player {
public:
    Player(const std::string &name);

    std::string GetName() const;

    VehiclePtr GetVehicle() const;

    void setTime(std::string map, int time);

    void save();
private:
    std::string name_;
    VehiclePtr vehicle_;
    std::map<std::string, int> times_;
    const std::string resourcePath_ = "../players/";
};

using PlayerPtr = std::shared_ptr<Player>;
