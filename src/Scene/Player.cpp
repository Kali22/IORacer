#include "Player.h"

Player::Player(const std::string &name, CarComponentManagerPtr carComponentManager, bool newPlayer)
        : name_(name) {
    if (newPlayer) {
        carConfiguration_ = std::make_shared<CarConfiguration>(carComponentManager->GetBaseComponents());
    } else {
        std::ifstream file(resourcePath_ + name_);
        std::string line;
        std::stringstream data;

        // read car configuration
        std::vector<CarComponentPtr> carComponents;
        getline(file, line);
        data = std::stringstream(line);
        for (int type = 0; type < MODIFIER_TYPE_MAX; type++) {
            int component_id;
            data >> component_id;
            carComponents.push_back(carComponentManager->GetComponent((ModifierType) type, component_id));
        }
        carConfiguration_ = std::make_shared<CarConfiguration>(carComponents);

        // read times
        std::string mapName;
        float time;
        while (getline(file, line)) {
            data = std::stringstream(line);
            data >> mapName >> time;
            times_[mapName] = time;
        }
    }
}


std::string Player::GetName() const {
    return name_;
}

CarConfigurationPtr Player::GetCarConfiguration() const {
    return carConfiguration_;
}

std::map<std::string, float> Player::GetTimes() const {
    std::map<std::string, float> ret = times_;
    return ret;
}

void Player::setTime(std::string map, float time) {
    if (time != std::numeric_limits<float>::infinity()) {
        auto it = times_.find(map);
        if (it == times_.end()) {
            times_[map] = time;
        } else {
            times_[map] = std::min(it->second, time);
        }
    }
}

void Player::save() {
    std::ofstream file(resourcePath_ + name_);
    // save car configuration
    for (auto id : carConfiguration_->GetComponentsIDs()) {
        file << id << " ";
    }
    file << std::endl;
    // save times
    for (auto &time : times_) {
        file << time.first << " " << time.second << std::endl;
    }
}
