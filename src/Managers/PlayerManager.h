#pragma once


#include <bits/stdc++.h>
#include <Player.h>
#include <CarComponentManager.h>

class PlayerManager {
public:
    PlayerManager(CarComponentManagerPtr carComponentManager);

    ~PlayerManager();

    bool SetActivePlayer(const std::string &name);

    bool SetSecondPlayer(const std::string &name);

    PlayerPtr GetActivePlayer() const;

    PlayerPtr GetSecondPlayer() const;

    PlayerPtr GetPlayer(const std::string &name) const;

    void CreateNewPlayer(const std::string &name);

    std::vector<std::string> GetPlayersList() const;

    void SaveGame();

private:
    std::map<std::string, PlayerPtr> nameToPlayer_;
    PlayerPtr activePlayer_;
    PlayerPtr secondPlayer_;
    CarComponentManagerPtr carComponentManager_;
    const std::string resourcePath_ = "../resource/players/";
    const std::string playerListFile_ = "players_list";

};

using PlayerManagerPtr = std::shared_ptr<PlayerManager>;
