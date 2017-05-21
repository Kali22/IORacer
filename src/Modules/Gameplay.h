#pragma once

#include <Activity.h>
#include "../Events/Event.h"
#include <Vehicle.h>
#include "../Managers/MapManager.h"

enum GameplayStateE {
    GAMEPLAY_STATE_PREPARE,
    GAMEPLAY_STATE_RUNNING,
    GAMEPLAY_STATE_PAUSE,
    GAMEPLAY_STATE_END
};

class Gameplay : public Activity {
public:
    Gameplay(const std::string &mapName, int laps);

    void SetFirstPlayer(const std::string &name);

    void SetSecondPlayer(const std::string &name);

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

    void PrepareUIForPrepareState();

    void PrepareUIForPauseState();

    void PrepareUIForEndState();

    void PrepareHUD();


    int laps_;
    std::string mapName_;

    float globalTime_; // Time in race
    GameplayStateE gameState_; // Game status

    /* Players */
    std::string firstPlayerName_;
    std::string secondPlayerName_;
    VehiclePtr firstPlayerVehicle_;
    VehiclePtr secondPlayerVehicle_;

    ScenePtr scene_;

    ObjectManagerPtr objectManager_;
    MapManagerPtr mapManager_;
    b2World *world_;

    const float preparationTimeInSeconds = 1.f;


    void HandleKeyFirstPlayer(sf::Event::KeyEvent event, bool state);

    void HandleKeySecondPlayer(sf::Event::KeyEvent event, bool state);

    void SetTitleStyle(UITextBoxPtr textBox);

    void PrintState();
};

using GameplayPtr = std::shared_ptr<Gameplay>;

