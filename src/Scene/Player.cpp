#include "Player.h"

Player::Player(const std::string &name, VehiclePtr vehicle)
        : name_(name), vehicle_(vehicle) {}

std::string Player::GetName() const {
    return name_;
}

VehiclePtr Player::GetVehicle() const {
    return vehicle_;
}
