#include "PlayerManager.h"

PlayerManager::PlayerManager() {
    std::ifstream file(resourcePath_ + playerListFile_);
    std::string line;

    while (getline(file, line)) {
        nameToPlayer_[line] = std::make_shared<Player>(line);
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

PlayerPtr PlayerManager::GetPlayer(const std::string &name) const {
    auto it = nameToPlayer_.find(name);
    if (it == nameToPlayer_.end()) {
        return nullptr;
    }
    return it->second;
}

std::vector<std::string> PlayerManager::GetPlayersList() const {
    std::vector<std::string> playersList;
    for (auto& player : nameToPlayer_) {
        playersList.push_back(player.first);
    }
    return playersList;
}

void PlayerManager::CreateNewPlayer(const std::string &name) {
    std::ofstream players_list(resourcePath_ + playerListFile_ , std::ios_base::app);
    players_list << name << std::endl;
    nameToPlayer_[name] = std::make_shared<Player>(name);
}

void PlayerManager::SaveGame() {
    for (auto& player : nameToPlayer_) {
        player.second->save();
    }
}

PlayerManager::~PlayerManager() {
    SaveGame();
}










