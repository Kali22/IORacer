#pragma once

#include <string>
#include <bits/stdc++.h>
#include <CarConfiguration.h>

/// TODO add achivements
class Player {
public:
    Player(const std::string &name);

    std::string GetName() const;

    CarConfigurationPtr GetCarConfiguration() const;

    std::map<std::string, float> GetTimes() const;

    void setTime(std::string map, float time);

    void save();
private:
    std::string name_;
    CarConfigurationPtr carConfiguration_;
    std::map<std::string, float> times_;
    const std::string resourcePath_ = "../players/";
};

using PlayerPtr = std::shared_ptr<Player>;
