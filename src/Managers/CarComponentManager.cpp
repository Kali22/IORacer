#include "CarComponentManager.h"


CarComponentManager::CarComponentManager() {
    typeToComponents_[ENGINE_POWER_MAX] = CreateEngineComponents();
    typeToComponents_[AERODYNAMIC_FRICTION] = CreateAerodynamicComponents();
    typeToComponents_[STEERING_ANGLE_MAX] = CreateWheelComponents();
    modifierToCategoryName_ = {
            {ENGINE_POWER_MAX,     "Engine"},
            {AERODYNAMIC_FRICTION, "Body"},
            {STEERING_ANGLE_MAX,   "Wheels"}
    };
}

CarComponentPtr CarComponentManager::GetComponent(ModifierType type,
                                                  int id) const {
    auto category = typeToComponents_.find(type);
    if (category == typeToComponents_.end()) {
        std::cerr << "Fatal: Requested unknown car component category"
                  << std::endl;
        exit(1);
    }
    auto components = category->second;
    if (id < 0 || id >= components.size()) {
        std::cerr << "Fatal: Requested unknown car component id"
                  << std::endl;
        exit(1);
    }
    return components[id];
}

std::vector<ComponentCategoryPtr> CarComponentManager::GetComponentCategories() const {
    std::vector<ComponentCategoryPtr> categories;
    for (auto it : typeToComponents_) {
        auto nameIt = modifierToCategoryName_.find(it.first);
        if (nameIt == modifierToCategoryName_.end()) {
            std::cerr << "Fatal: Unknown category name" << std::endl;
            exit(1);
        }
        std::string name = nameIt->second;
        categories.push_back(std::make_shared<ComponentCategory>(
                it.first, name, it.second));
    }
    return categories;
}


std::vector<CarComponentPtr> CarComponentManager::CreateEngineComponents() {
    std::vector<CarComponentPtr> components;
    components.push_back(std::make_shared<CarComponent>(
            ENGINE_POWER_MAX, 0, "Engine 1", std::map<std::string, float>(),
            60000));

    std::map<std::string, float> requirement = {{"map_1", 17}};
    components.push_back(std::make_shared<CarComponent>(
            ENGINE_POWER_MAX, 1, "Engine 2", requirement, 110000));
    requirement = {{"map_0", 12.},
                   {"map_1", 17}};
    components.push_back(std::make_shared<CarComponent>(
            ENGINE_POWER_MAX, 2, "Engine 3", requirement,
            200000));
    return components;
}

std::vector<CarComponentPtr>
CarComponentManager::CreateAerodynamicComponents() {
    std::vector<CarComponentPtr> components;
    components.push_back(std::make_shared<CarComponent>(
            AERODYNAMIC_FRICTION, 0, "Body 1", std::map<std::string, float>(), 0.1));

    std::map<std::string, float> requirement = {{"map_1", 16}};
    components.push_back(std::make_shared<CarComponent>(
            AERODYNAMIC_FRICTION, 1, "Body 2", requirement, 0.01));
    requirement = {{"map_0", 11.},
                   {"map_1", 15}};
    components.push_back(std::make_shared<CarComponent>(
            AERODYNAMIC_FRICTION, 2, "Body 3", requirement, 0.001));
    return components;

}

std::vector<CarComponentPtr> CarComponentManager::CreateWheelComponents() {
    std::vector<CarComponentPtr> components;
    components.push_back(std::make_shared<CarComponent>(
            STEERING_ANGLE_MAX, 0, "Wheel 1", std::map<std::string, float>(),
            10));

    std::map<std::string, float> requirement = {{"map_0", 13}};
    components.push_back(std::make_shared<CarComponent>(
            STEERING_ANGLE_MAX, 1, "Wheel 2", requirement,
            20));
    requirement = {{"map_0", 12.},
                   {"map_1", 14}};
    components.push_back(std::make_shared<CarComponent>(
            STEERING_ANGLE_MAX, 2, "Wheel 3", requirement,
            30));
    return components;

}

std::vector<CarComponentPtr> CarComponentManager::GetBaseComponents() const {
    std::vector<CarComponentPtr> components;
    components.push_back(typeToComponents_.at(ENGINE_POWER_MAX)[0]);
    components.push_back(typeToComponents_.at(AERODYNAMIC_FRICTION)[0]);
    components.push_back(typeToComponents_.at(STEERING_ANGLE_MAX)[0]);
    return components;
}