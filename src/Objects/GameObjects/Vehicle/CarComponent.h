#pragma once

#include <map>
#include <vector>
#include <string>
#include <bits/stdc++.h>

enum ModifierType {
    ENGINE_POWER_MAX,
    AERODYNAMIC_FRICTION,
    STEERING_ANGLE_MAX
};

class CarComponent {
public:
    CarComponent(ModifierType type, int id, const std::string& name,
                 std::map<std::string, float> requirement, float value);

    ModifierType GetType() const;

    float GetValue() const;

    std::string GetName() const;

    int GetId() const;

    bool IsTimesSufficient(std::map<std::string, float> times) const;

    std::map<std::string, float> GetRequirement() const;
private:
    ModifierType type_;
    int id_;
    std::string name_;
    float value_;
    std::map<std::string, float> mapNameToTime_;
};


using CarComponentPtr = std::shared_ptr<CarComponent>;