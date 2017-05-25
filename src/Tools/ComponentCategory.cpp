#include "ComponentCategory.h"

ComponentCategory::ComponentCategory(ModifierType type, const std::string &name,
                                     std::vector<CarComponentPtr> components)
        : type_(type), name_(name), components_(components), current_(0) {}

bool ComponentCategory::SetComponent(int id) {
    if (id < 0 || id > components_.size()) {
        return false;
    }
    current_ = id;
    return true;
}

CarComponentPtr ComponentCategory::GetComponent() const {
    return components_[current_];
}

CarComponentPtr ComponentCategory::NextComponent() {
    current_ = (current_ + 1) % components_.size();
    return components_[current_];
}

CarComponentPtr ComponentCategory::PreviousComponent() {
    int size = components_.size();
    current_ = (current_ + size - 1) % size;
    return components_[current_];
}

std::string ComponentCategory::GetName() const {
    return name_;
}

ModifierType ComponentCategory::GetType() const {
    return type_;
}

