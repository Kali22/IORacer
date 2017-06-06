#include <PlayerManager.h>

PlayerManager::PlayerManager(CarComponentManagerPtr carComponentManager) :
        carComponentManager_(carComponentManager),
        activePlayer_(nullptr),
        secondPlayer_(nullptr) {
    std::ifstream file(resourcePath_ + playerListFile_);
    std::string line;

    while (getline(file, line)) {
        nameToPlayer_[line] = std::make_shared<Player>(line, carComponentManager_, false);
    }
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

PlayerPtr PlayerManager::GetSecondPlayer() const {
    return secondPlayer_;
}

bool PlayerManager::SetSecondPlayer(const std::string &name) {
    auto it = nameToPlayer_.find(name);
    if (it == nameToPlayer_.end()) {
        return false;
    }
    secondPlayer_ = it->second;
    return true;
}

PlayerPtr PlayerManager::GetPlayer(const std::string &name) const {
    auto it = nameToPlayer_.find(name);
    if (it == nameToPlayer_.end()) {
        return nullptr;
    }
    return it->second;
}

std::vector<std::string> PlayerManager::GetPlayersList() const {
    std::vector<std::string> playersList;
    for (auto &player : nameToPlayer_) {
        playersList.push_back(player.first);
    }
    return playersList;
}

void PlayerManager::CreateNewPlayer(const std::string &name) {
    std::ofstream players_list(resourcePath_ + playerListFile_, std::ios_base::app);
    players_list << std::endl << name;
    PlayerPtr player = std::make_shared<Player>(name, carComponentManager_, true);
    nameToPlayer_[name] = player;
}

void PlayerManager::SaveGame() {
    for (auto &player : nameToPlayer_) {
        player.second->save();
    }
}

PlayerManager::~PlayerManager() {
    SaveGame();
}
