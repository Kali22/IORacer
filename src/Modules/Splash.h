#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <Activity.h>
#include <Texture.h>
#include <Event.h>

class Splash : public Activity {
public:
    Splash();

    void Init();

    void Run();

    void End();

    void EventAction(Event event);

private:

    void HandleKey(sf::Event::KeyEvent event);
};

using SplashPtr = std::shared_ptr<Splash>;