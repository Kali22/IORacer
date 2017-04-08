//
// Created by pawel on 04.04.17.
//

#include <cassert>
#include <CheckPoint.h>
#include <CheckPointManager.h>
#include <SFML/System/Clock.hpp>

CheckPointManager::CheckPointManager(std::vector<CheckPoint*> checkPoints)
        :checkPoints_(checkPoints), finishedLap_(0), currentCheckPoint_(0) {
    assert(!checkPoints.empty());
    for (auto *checkPoint : checkPoints) {
        checkPoint->SetObserver(this);
    }
}

void CheckPointManager::Initialize() {
    GetCurrentCheckPoint()->SetEnable(false);
    currentCheckPoint_ = 0;
    finishedLap_ = 0;
    GetCurrentCheckPoint()->SetEnable(true);
    clock_.restart();
}

sf::Time CheckPointManager::GetElapsedTime() const {
    clock_.getElapsedTime();
}

void CheckPointManager::NotifyCheckPointReached() {
    if (GetCurrentCheckPoint()->IsEnabled()) {
        return;
    }
    currentCheckPoint_++;
    if (currentCheckPoint_ >= checkPoints_.size()) {
        finishedLap_++;
        currentCheckPoint_ = 0;
    }
    GetCurrentCheckPoint()->SetEnable(true);
}

void CheckPointManager::Draw(sf::RenderWindow* window) const {
    auto* checkPoint = GetCurrentCheckPoint();
    checkPoint->Draw(window);
}

CheckPoint* CheckPointManager::GetCurrentCheckPoint() const {
    return checkPoints_[currentCheckPoint_];
}

