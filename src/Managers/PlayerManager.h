#pragma once

#include <map>
#include <Player.h>


class PlayerManager {
public:
    PlayerManager();

    ~PlayerManager();

    bool SetActivePlayer(const std::string& name);

    PlayerPtr GetActivePlayer() const;

    PlayerPtr GetPlayer(const std::string& name) const;

    void CreateNewPlayer(const std::string& name);

    std::vector<std::string> GetPlayersList() const;

    void SaveGame();
private:
    std::map<std::string, PlayerPtr> nameToPlayer_;
    PlayerPtr activePlayer_;
    const std::string resourcePath_ = "../players/";
    const std::string playerListFile_ = "players_list";

};

using PlayerManagerPtr = std::shared_ptr<PlayerManager>;
