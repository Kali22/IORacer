#pragma once

#include <Activity.h>
#include <Event.h>

enum RaceType {
    SINGLE_PLAYER,
    MULTI_PLAYER
};

class NewRace : public Activity {
public:
    NewRace(RaceType type);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void Update();

    void HandleKey(sf::Event::KeyEvent event);

    void SetTitleStyle(UITextBoxPtr textBox);

    void SetButtonStyle(UITextBoxPtr button);

    void CreateRace(std::string name);

    RaceType type_;

    int laps_;
};

using NewRacePtr = std::shared_ptr<NewRace>;
