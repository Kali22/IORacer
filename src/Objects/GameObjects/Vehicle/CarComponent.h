#pragma once


#include <bits/stdc++.h>

enum ModifierTypeE {
    ENGINE_POWER_MAX,
    AERODYNAMIC_FRICTION,
    STEERING_ANGLE_MAX,
    MODIFIER_TYPE_MAX,
};

class CarComponent {
public:
    CarComponent(ModifierTypeE type, int id, const std::string &name,
                 std::map<std::string, float> requirement, float value);

    ModifierTypeE GetType() const;

    float GetValue() const;

    std::string GetName() const;

    int GetId() const;

    bool AreTimesSufficient(std::map<std::string, float> times) const;

    std::map<std::string, float> GetRequirement() const;

private:
    ModifierTypeE type_;
    int id_;
    std::string name_;
    float value_;
    std::map<std::string, float> mapNameToTime_;
};

using CarComponentPtr = std::shared_ptr<CarComponent>;
