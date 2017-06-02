#pragma once


#include <Activity.h>
#include <Event.h>

class MainMenu : public Activity {
public:
    MainMenu();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void HandleKey(sf::Event::KeyEvent event);

    void Update();

    void SetButtons();

    void HandleUIEventClick(Event event);

    void StartNewRace();

    void StartSecondPlayerSelector();

    void StartWorkshop();

    void StartFirstPlayerSelector();

    void QuitGame();
};

using MainMenuPtr = std::shared_ptr<MainMenu>;
