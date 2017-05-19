#pragma once


#include <Activity.h>
#include "../Events/Event.h"

class PlayerSelector : public Activity {
public:
    PlayerSelector();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:

    void HandleKey(sf::Event::KeyEvent event);

    void SetButtonStyle(UITextBoxPtr button);
};

using PlayerSelectorPrt = std::shared_ptr<PlayerSelector>;
