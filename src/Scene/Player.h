#pragma once

#include <string>
#include <bits/stdc++.h>
#include <CarConfiguration.h>

/// TODO add achivements
class Player {
public:
    Player(const std::string& name, CarConfigurationPtr carConfiguration);

    std::string GetName() const;

    CarConfigurationPtr GetCarConfiguration() const;
private:
    std::string name_;
    CarConfigurationPtr carConfiguration_;
};

using PlayerPtr = std::shared_ptr<Player>;
