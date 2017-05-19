#pragma once

#include <Activity.h>
#include "../Events/Event.h"

class NewRace : public Activity {
public:
    NewRace();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void HandleKey(sf::Event::KeyEvent event);

    void SetTitleStyle(UITextBoxPtr textBox);

    void CreateRace();
};

using NewRacePtr = std::shared_ptr<NewRace>;

