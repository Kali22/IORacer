#include "CarComponentManager.h"

CarComponentManager::CarComponentManager() {
    typeToComponents_[ENGINE_POWER_MAX] = CreateEngineComponents();
    typeToComponents_[AERODYNAMIC_FRICTION] = CreateAerodynamicComponents();
    typeToComponents_[STEERING_ANGLE_MAX] = CreateWheelComponents();
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

std::vector<CarComponentPtr> CarComponentManager::CreateEngineComponents() {
    std::vector<CarComponentPtr> components;
    components.push_back(std::make_shared<CarComponent>(
            ENGINE_POWER_MAX, 0, "Silnik 1", std::map<std::string, float>(), 60000));

    components.push_back(std::make_shared<CarComponent>(
            ENGINE_POWER_MAX, 1, "Silnik 2", std::map<std::string, float>(), 11000));
    components.push_back(std::make_shared<CarComponent>(
            ENGINE_POWER_MAX, 2, "Silnik 3", std::map<std::string, float>(), 20000));
    return components;
}

std::vector<CarComponentPtr>
CarComponentManager::CreateAerodynamicComponents() {
    std::vector<CarComponentPtr> components;
    components.push_back(std::make_shared<CarComponent>(
            AERODYNAMIC_FRICTION, 0, "Karoseria 1", std::map<std::string, float>(), 0.1));
    components.push_back(std::make_shared<CarComponent>(
            AERODYNAMIC_FRICTION, 1, "Karoseria 2", std::map<std::string, float>(), 0.01));
    components.push_back(std::make_shared<CarComponent>(
            AERODYNAMIC_FRICTION, 2, "Karoseria 3", std::map<std::string, float>(), 0.001));
    return components;

}

std::vector<CarComponentPtr> CarComponentManager::CreateWheelComponents() {
    std::vector<CarComponentPtr> components;
    components.push_back(std::make_shared<CarComponent>(
            STEERING_ANGLE_MAX, 0, "Koło 1", std::map<std::string, float>(), 10));
    components.push_back(std::make_shared<CarComponent>(
            STEERING_ANGLE_MAX, 1, "Koło 2", std::map<std::string, float>(), 20));
    components.push_back(std::make_shared<CarComponent>(
            STEERING_ANGLE_MAX, 2, "Koło 3", std::map<std::string, float>(), 30));
    return components;

}
