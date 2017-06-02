#pragma once


#include <string>
#include <bits/stdc++.h>
#include <CarConfiguration.h>
#include <CarComponentManager.h>

class Player {
public:
    Player(const std::string &name, CarComponentManagerPtr carComponentManager, bool newPlayer);

    std::string GetName() const;

    CarConfigurationPtr GetCarConfiguration() const;

    std::map<std::string, float> GetTimes() const;

    void setTime(std::string map, float time);

    void save();

private:
    std::string name_;
    CarConfigurationPtr carConfiguration_;
    std::map<std::string, float> times_;
    const std::string resourcePath_ = "../resource/players/";

    void ParseConfiguration(std::ifstream &file, CarComponentManagerPtr);
};

using PlayerPtr = std::shared_ptr<Player>;
