#pragma once

#define MAX_PLAYER 2

#include <Activity.h>
#include <Event.h>
#include <Vehicle.h>
#include <ContactListener.h>
#include <MapManager.h>
#include <Player.h>
#include <UIMinimap.h>

enum GameplayStateE {
    GAMEPLAY_STATE_PREPARE,
    GAMEPLAY_STATE_RUNNING,
    GAMEPLAY_STATE_PAUSE,
    GAMEPLAY_STATE_END
};

class Gameplay : public Activity {
public:
    Gameplay(const std::string &mapName, int laps);

    void SetFirstPlayer(PlayerPtr player);

    void SetSecondPlayer(PlayerPtr player);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void HandleKey(sf::Event::KeyEvent event, bool state);

    void HandleKeyInPauseState(sf::Event::KeyEvent event);

    void HandleKeyInGameState(sf::Event::KeyEvent event, bool state);

    void HandleKeyInPrepareState(sf::Event::KeyEvent event);

    void HandleKeyInEndState(sf::Event::KeyEvent event);

    void Update();

    void Render();

    void ExitGame();

    void UpdateUIInPrepareState();

    void UpdateUIInPauseState();

    void UpdateUIInEndState();

    void UpdateHUD();

    void UpdateGame();

    void UpdatePlayer(int id, float dt);

    void PrepareUIForPrepareState();

    void PrepareUIForPauseState();

    void PrepareUIForEndState();

    void PrepareHUD();

    void PreparePlayer(int id);

    /* xD xD xD */
    bool isOver_;
    std::string winnerName_;

    int laps_;
    std::string mapName_;

    float globalTime_; // Time in race
    GameplayStateE gameState_; // Game status

    /* Players */
    PlayerPtr player_[MAX_PLAYER];
    VehiclePtr playerVehicle_[MAX_PLAYER];
    CheckPointManagerPtr playerCheckpoints_[MAX_PLAYER];

    MapPtr map_;
    ScenePtr scene_;
    ObjectManagerPtr objectManager_;
    MapManagerPtr mapManager_;
    ContactListenerPtr contactListener_;
    b2World *world_;

    UIMinimapPtr minimap_[MAX_PLAYER];

    const float preparationTimeInSeconds = 3.f;

    void HandleKeyFirstPlayer(sf::Event::KeyEvent event, bool state);

    void HandleKeySecondPlayer(sf::Event::KeyEvent event, bool state);

    void SetTitleStyle(UITextBoxPtr textBox);

    void SaveTimes();
};

using GameplayPtr = std::shared_ptr<Gameplay>;
