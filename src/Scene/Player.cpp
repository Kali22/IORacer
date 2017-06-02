#include <Player.h>

Player::Player(const std::string &name, CarComponentManagerPtr carComponentManager, bool newPlayer) : name_(name) {
    if (newPlayer) {
        carConfiguration_ = std::make_shared<CarConfiguration>(carComponentManager->GetBaseComponents());
    } else {
        std::ifstream file(resourcePath_ + name_);
        ParseConfiguration(file, carComponentManager);

        // read times
        std::string mapName;
        float time;
        while (file >> mapName >> time) {
            times_[mapName] = time;
        }
    }
}

void Player::ParseConfiguration(std::ifstream &file, CarComponentManagerPtr carComponentManager) {
    std::vector<CarComponentPtr> carComponents;
    int component_id;
    for (int type = 0; type < MODIFIER_TYPE_MAX; type++) {
        file >> component_id;
        carComponents.push_back(carComponentManager->GetComponent((ModifierType) type, component_id));
    }
    carConfiguration_ = std::make_shared<CarConfiguration>(carComponents);
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
