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

    std::vector<int> GetComponentsIDs() const;

    void AddComponent(CarComponentPtr component);

    /** Return -1 if there is no component from given category. */
    int GetComponentId(ModifierType) const;

private:
    float GetModifierByType(ModifierType type) const;

    std::map<ModifierType, CarComponentPtr> components_;
};


using CarConfigurationPtr = std::shared_ptr<CarConfiguration>;