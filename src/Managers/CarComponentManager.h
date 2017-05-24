#pragma once

#include <map>
#include <vector>
#include <CarComponent.h>

class CarComponentManager {
public:
    CarComponentManager();

    CarComponentPtr GetComponent(ModifierType type, int id) const;
private:
    static std::vector<CarComponentPtr> CreateEngineComponents();

    static std::vector<CarComponentPtr> CreateAerodynamicComponents();

    static std::vector<CarComponentPtr> CreateWheelComponents();

    std::map<ModifierType, std::vector<CarComponentPtr>> typeToComponents_;
};