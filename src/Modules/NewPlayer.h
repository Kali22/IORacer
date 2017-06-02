#pragma once


#include <Activity.h>
#include <Event.h>
#include <PlayerSelector.h>

class NewPlayer : public Activity {
public:
    NewPlayer(SelectorType type);

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void HandleKey(sf::Event::KeyEvent event);

    void Update();

    void CreatePlayer();

    std::string player_;

    SelectorType type_;

    const std::string resourcePath_ = "../players/";

    void HandleSFMLEvent(Event event);
};

using NewPlayerPtr = std::shared_ptr<NewPlayer>;
