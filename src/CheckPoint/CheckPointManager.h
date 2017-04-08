#pragma once

#include <CheckPoint.h>
#include <CheckPointObserver.h>
#include <SFML/System/Clock.hpp>
#include <Drawable.h>

class CheckPointManager : public CheckPointObserver, public Drawable {
public:
    CheckPointManager(std::vector<CheckPointPtr> checkPoints);

    void Reset();

    sf::Time GetElapsedTime() const;

    void NotifyCheckPointReached();

    void Draw(sf::RenderWindow *window) const;

private:
    CheckPointPtr GetCurrentCheckPoint() const;

    std::vector<CheckPointPtr> checkPoints_;
    int finishedLap_;
    int currentCheckPoint_;
    sf::Clock clock_;
};

using CheckPointManagerPtr = std::shared_ptr<CheckPointManager>;
