#include "CarComponent.h"

CarComponent::CarComponent(ModifierType type, const std::string &name,
                           std::map<std::string, float> requirement,
                           float value)
        : type_(type), name_(name), requirement_(requirement), value_(value) {}


ModifierType CarComponent::GetType() const {
    return type_;
}

float CarComponent::GetValue() const {
    return value_;
}

std::string CarComponent::GetName() const {
    return name_;
}

std::map<std::string, float> CarComponent::GetRequirement() const {
    return requirement_;
}

