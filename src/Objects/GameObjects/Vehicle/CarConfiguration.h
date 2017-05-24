#pragma once

#include <map>
#include <string>
#include <vector>
#include <CarComponent.h>


class CarConfiguration {
public:
    CarConfiguration(std::vector<CarComponentPtr> carComponents);

    float GetEnginePowerMax() const;

    float GetAerodynamicFriction() const;

    float GetSteeringAngleMax() const;

    void AddComponent(CarComponentPtr component);
private:
    float GetModifierByType(ModifierType type) const;

    std::map<ModifierType, CarComponentPtr> components_;
};

