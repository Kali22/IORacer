#include "CarComponent.h"

CarComponent::CarComponent(ModifierType type, int id, const std::string &name,
                           std::map<std::string, float> requirement,
                           float value)
        : type_(type), id_(id), name_(name), mapNameToTime_(requirement),
          value_(value) {}

ModifierType CarComponent::GetType() const {
    return type_;
}

float CarComponent::GetValue() const {
    return value_;
}

std::string CarComponent::GetName() const {
    return name_;
}

int CarComponent::GetId() const {
    return id_;
}

std::map<std::string, float> CarComponent::GetRequirement() const {
    return mapNameToTime_;
}

bool CarComponent::IsTimesSufficient(std::map<std::string, float> userTimes) const {
    for (auto time : mapNameToTime_) {
        auto userTime = userTimes.find(time.first);
        if (userTime == userTimes.end() || userTime->second > time.second) {
            return false;
        }
    }
    return true;
}
