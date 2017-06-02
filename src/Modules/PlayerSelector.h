#pragma once


#include <Activity.h>
#include <Event.h>

enum SelectorType {
    FIRST_PLAYER,
    SECOND_PLAYER
};

class PlayerSelector : public Activity {
public:
    PlayerSelector(SelectorType type);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void ShowPlayers();

    void UpdatePlayersList();

    void EmplaceNewPlayerControls();

    void HandleUIEventClick(Event event);

    void SelectPlayer();

    void HandleKey(sf::Event::KeyEvent event);

    void Update();

    size_t player_;
    std::vector<std::string> playersList_;
    SelectorType type_;
};

using PlayerSelectorPtr = std::shared_ptr<PlayerSelector>;
