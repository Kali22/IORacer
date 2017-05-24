#include "PlayerManager.h"

PlayerManager::PlayerManager() {
}

PlayerPtr PlayerManager::GetActivePlayer() const {
    return activePlayer_;
}

bool PlayerManager::SetActivePlayer(const std::string &name) {
    auto it = nameToPlayer_.find(name);
    if (it == nameToPlayer_.end()) {
        return false;
    }
    activePlayer_ = it->second;
    return true;
}

PlayerPtr PlayerManager::GetPlayer(const std::string &name) const {
    auto it = nameToPlayer_.find(name);
    if (it == nameToPlayer_.end()) {
        return nullptr;
    }
    return it->second;
}


