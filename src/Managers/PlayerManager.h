#pragma once

#include <bits/stdc++.h>
#include <map>
#include <Player.h>


class PlayerManager {
public:
    PlayerManager();

    bool SetActivePlayer(const std::string& name);

    PlayerPtr GetActivePlayer() const;

    PlayerPtr GetPlayer(const std::string& name) const;

    // bool CreateNewPlayer(const std::string& name) const;

    // std::vector<std::string> GetPlayersList() const;
private:
    std::map<std::string, PlayerPtr> nameToPlayer_;
    PlayerPtr activePlayer_;
};
using PlayerManagerPtr = std::shared_ptr<PlayerManager>;
