#pragma once
//
// Created by pawel on 04.04.17.
//

#include <CheckPoint.h>
#include <CheckPointObserver.h>
#include <SFML/System/Clock.hpp>


class CheckPointManager : public CheckPointObserver {
public:
    void StartTimer();

    sf::Time GetElapsedTime();

    void NotifyCheckPointReached();

    void DrawCheckPoints(sf::RenderWindow* window);

    CheckPointManager(std::vector<CheckPoint*> checkPoints);
private:
    CheckPoint* GetCurrentCheckPoint();

    std::vector<CheckPoint*> checkPoints_;
    int finishedLap_;
    int currentCheckPoint_;
    sf::Clock clock_;
};

