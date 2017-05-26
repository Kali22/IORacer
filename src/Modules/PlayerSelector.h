#pragma once


#include <Activity.h>
#include <Event.h>

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

    void SetTextBoxStyle(UITextBoxPtr textBox);

    void Update();

    size_t player_;

    std::vector<std::string> playersList_;
};

using PlayerSelectorPtr = std::shared_ptr<PlayerSelector>;
