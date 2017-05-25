#pragma once

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <CarConfiguration.h>
#include <CarComponent.h>

class ComponentCategory {
public:
    ComponentCategory(ModifierType type, const std::string& name,
                      std::vector<CarComponentPtr> components);

    std::string GetName() const;

    bool SetComponent(int id);

    CarComponentPtr GetComponent() const;

    CarComponentPtr NextComponent();

    CarComponentPtr PreviousComponent();
private:
    std::vector<CarComponentPtr> components_;
    int current_;
    ModifierType type_;
    std::string name_;
};
using ComponentCategoryPtr = std::shared_ptr<ComponentCategory>;
