#pragma once


#include <Activity.h>
#include <Event.h>

enum RaceTypeE {
    SINGLE_PLAYER,
    MULTI_PLAYER
};

class NewRace : public Activity {
public:
    NewRace(RaceTypeE type);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void Update();

    void HandleKey(sf::Event::KeyEvent event);

    void CreateRace(std::string name);

    RaceTypeE type_;

    int laps_;

    void SetLaps();

    void SetMaps();

    void HandleUIEventClick(Event event);
};

using NewRacePtr = std::shared_ptr<NewRace>;
