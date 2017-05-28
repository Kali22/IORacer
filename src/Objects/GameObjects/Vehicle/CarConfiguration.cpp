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
    std::cout << "Added component " << component->GetName() << " to car" << std::endl;
}

std::vector<int> CarConfiguration::GetComponentsIDs() const {
    std::vector<int> IDs;
    for (auto component : components_) {
        IDs.push_back(component.second->GetId());
    }
    return IDs;
}


int CarConfiguration::GetComponentId(ModifierType type) const {
    auto it = components_.find(type);
    if (it == components_.end()) {
        return -1;
    }
    return it->second->GetId();
}

