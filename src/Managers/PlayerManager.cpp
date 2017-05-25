#include "PlayerManager.h"
#include "CarComponentManager.h"

PlayerManager::PlayerManager() {
    // TODO Use stored player - integrate with player branch.
    CarComponentManagerPtr carComponentManager = std::make_shared<CarComponentManager>();
    std::vector<CarComponentPtr> carComponents = carComponentManager->GetBaseComponents();
    CarConfigurationPtr carConfiguration =
            std::make_shared<CarConfiguration>(carComponents);

    PlayerPtr player = std::make_shared<Player>("jacek", carConfiguration);
    nameToPlayer_.emplace("jacek", player);
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


