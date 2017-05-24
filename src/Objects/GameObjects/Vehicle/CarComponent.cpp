#include "CarComponent.h"

CarComponent::CarComponent(ModifierType type, int id, const std::string &name,
                           std::map<std::string, float> requirement,
                           float value)
        : type_(type), id_(id), name_(name), requirement_(requirement),
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
    return requirement_;
}

