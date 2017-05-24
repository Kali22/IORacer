#include "CarConfiguration.h"

CarConfiguration::CarConfiguration(
        std::vector<CarComponentPtr> carComponents) {
    for (auto carComponent : carComponents) {
        components_[carComponent->GetType()] = carComponent;
    }
}

float CarConfiguration::GetEnginePowerMax() const {
    return GetModifierByType(ENGINE_POWER_MAX);
}

float CarConfiguration::GetAerodynamicFriction() const {
    return GetModifierByType(AERODYNAMIC_FRICTION);
}

float CarConfiguration::GetSteeringAngleMax() const {
    return GetModifierByType(STEERING_ANGLE_MAX);
}

float CarConfiguration::GetModifierByType(ModifierType type) const {
    auto it = components_.find(type);
    if (it == components_.end()) {
        return 0;
    }
    return it->second->GetValue();
}

void CarConfiguration::AddComponent(CarComponentPtr component) {
    components_[component->GetType()] = component;
}
