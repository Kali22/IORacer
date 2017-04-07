//
// Created by pawel on 04.04.17.
//

#include <cassert>
#include <CheckPoint.h>
#include <CheckPointManager.h>
#include <SFML/System/Clock.hpp>

void CheckPointManager::StartTimer() {
    if (checkPoints_.empty()) {
        return;
    }
    GetCurrentCheckPoint()->Enable();
    clock_.restart();
}

sf::Time CheckPointManager::GetElapsedTime() {
    clock_.getElapsedTime();
}

void CheckPointManager::NotifyCheckPointReached() {
    if (GetCurrentCheckPoint()->IsEnabled()) {
        return;
    }
    // TODO save time
    currentCheckPoint_++;
    if (currentCheckPoint_ >= checkPoints_.size()) {
        finishedLap_++;
        currentCheckPoint_ = 0;
    }
    GetCurrentCheckPoint()->Enable();
}

CheckPointManager::CheckPointManager(std::vector<CheckPoint*> checkPoints)
        :checkPoints_(checkPoints), finishedLap_(0), currentCheckPoint_(0) {
    assert(!checkPoints.empty());
    for (auto *checkPoint : checkPoints) {
        checkPoint->SetObserver(this);
    }
}

void CheckPointManager::DrawCheckPoints(sf::RenderWindow* window) {
    auto* checkPoint = GetCurrentCheckPoint();
    checkPoint->Draw(window);
}

CheckPoint* CheckPointManager::GetCurrentCheckPoint() {
    return checkPoints_[currentCheckPoint_];
}

