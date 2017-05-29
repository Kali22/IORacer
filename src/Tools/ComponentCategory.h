#pragma once


#include <string>
#include <bits/stdc++.h>
#include <CarConfiguration.h>
#include <CarComponent.h>

class ComponentCategory {
public:
    ComponentCategory(ModifierType type, const std::string &name,
                      std::vector<CarComponentPtr> components);

    std::string GetName() const;

    ModifierType GetType() const;

    bool SetComponent(unsigned long id);

    CarComponentPtr GetComponent() const;

    CarComponentPtr NextComponent();

    CarComponentPtr PreviousComponent();

private:
    std::vector<CarComponentPtr> components_;
    unsigned long current_;
    ModifierType type_;
    std::string name_;
};

using ComponentCategoryPtr = std::shared_ptr<ComponentCategory>;
