#pragma once

#include <Activity.h>
#include <Event.h>

class Gameplay : public Activity {
public:
    Gameplay();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:
    void HandleKey(sf::Event::KeyEvent event);

    ScenePtr scene_;

};

using GameplayPtr = std::shared_ptr<Gameplay>;

