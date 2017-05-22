#pragma once

#include <Activity.h>
#include <Event.h>

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

    void SetButtonStyle(UITextBoxPtr button);

    void CreateRace(std::string name);
};

using NewRacePtr = std::shared_ptr<NewRace>;

