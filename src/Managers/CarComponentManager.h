#pragma once


#include <bits/stdc++.h>
#include <CarComponent.h>
#include <ComponentCategory.h>

class CarComponentManager {
public:
    CarComponentManager();

    CarComponentPtr GetComponent(ModifierType type, int id) const;

    std::vector<ComponentCategoryPtr> GetComponentCategories() const;

    std::vector<CarComponentPtr> GetBaseComponents() const;

private:
    static std::vector<CarComponentPtr> CreateEngineComponents();

    static std::vector<CarComponentPtr> CreateAerodynamicComponents();

    static std::vector<CarComponentPtr> CreateWheelComponents();

    std::map<ModifierType, std::string> modifierToCategoryName_;

    std::map<ModifierType, std::vector<CarComponentPtr>> typeToComponents_;
};

using CarComponentManagerPtr = std::shared_ptr<CarComponentManager>;
