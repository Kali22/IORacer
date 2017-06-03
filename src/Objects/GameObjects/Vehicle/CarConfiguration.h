#pragma once


#include <bits/stdc++.h>
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
    int GetComponentId(ModifierTypeE) const;

private:
    float GetModifierByType(ModifierTypeE type) const;

    std::map<ModifierTypeE, CarComponentPtr> components_;
};

using CarConfigurationPtr = std::shared_ptr<CarConfiguration>;
