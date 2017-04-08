#pragma once

#include <CheckPoint.h>
#include <CheckPointObserver.h>
#include <SFML/System/Clock.hpp>
#include <Drawable.h>

class CheckPointManager : public CheckPointObserver, public Drawable {
public:
    CheckPointManager(std::vector<CheckPoint*> checkPoints);

    void Initialize();
    sf::Time GetElapsedTime() const;

    void NotifyCheckPointReached();
    void Draw(sf::RenderWindow* window) const;
private:
    CheckPoint* GetCurrentCheckPoint() const;

    std::vector<CheckPoint*> checkPoints_;
    int finishedLap_;
    int currentCheckPoint_;
    sf::Clock clock_;
};

