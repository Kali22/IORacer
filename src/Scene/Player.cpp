#include "Player.h"

Player::Player(const std::string &name)
        : name_(name) {
    std::ifstream file(resourcePath_ + name_);
    std::string line;
    std::stringstream data;
    std::string mapName;
    float time;

    while (getline(file, line)) {
        data = std::stringstream(line);
        data >> mapName >> time;
        times_[mapName] = time;
    }
}


std::string Player::GetName() const {
    return name_;
}

CarConfigurationPtr Player::GetCarConfiguration() const {
    return carConfiguration_;
}

std::map<std::string, float> Player::GetTimes() const {
    return times_;
}

void Player::setTime(std::string map, float time) {
    auto it = times_.find(map);
    if (it == times_.end()) {
        times_[map] = time;
    }
    else {
        times_[map] = std::min(it->second, time);
    }
}

void Player::save() {
    std::ofstream file(resourcePath_ + name_);
    for (auto& time : times_) {
        file << time.first << " " << time.second << std::endl;
    }
}
