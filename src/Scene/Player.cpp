#include "Player.h"

Player::Player(const std::string &name, CarConfigurationPtr carConfiguration)
        : name_(name), carConfiguration_(carConfiguration) {}

std::string Player::GetName() const {
    return name_;
}

CarConfigurationPtr Player::GetCarConfiguration() const {
    return carConfiguration_;
}
