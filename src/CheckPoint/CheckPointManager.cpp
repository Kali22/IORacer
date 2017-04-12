//
// Created by pawel on 04.04.17.
//
#include <cassert>
#include <CheckPoint.h>
#include <CheckPointManager.h>

CheckPointManager::CheckPointManager(std::vector<CheckPointPtr> checkPoints)
        : checkPoints_(checkPoints), finishedLap_(0), currentCheckPoint_(0) {
    assert(!checkPoints.empty());
    for (auto checkPoint : checkPoints) {
        checkPoint->SetObserver(this);
    }
}

void CheckPointManager::Reset() {
    GetCurrentCheckPoint()->SetEnable(false);
    currentCheckPoint_ = 0;
    finishedLap_ = 0;
    GetCurrentCheckPoint()->SetEnable(true);
    clock_.restart();

    /// @TODO ???? End of race conditions?
    totalLaps_ = 100;
}

sf::Time CheckPointManager::GetElapsedTime() const {
    return clock_.getElapsedTime();
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

void CheckPointManager::Draw(sf::RenderWindow *window) const {
    auto checkPoint = GetCurrentCheckPoint();
    checkPoint->Draw(window);
}

CheckPointPtr CheckPointManager::GetCurrentCheckPoint() const {
    return checkPoints_[currentCheckPoint_];
}

sf::Vector2f CheckPointManager::GetNextCheckPointPosition() const {
    return GetCurrentCheckPoint()->GetPosition();
}

float CheckPointManager::GetLastLapTime() const {
    return 0;
}

float CheckPointManager::GetBestLapTime() const {
    return 0;
}

int CheckPointManager::GetCurrentLap() const {
    return finishedLap_;
}

int CheckPointManager::GetTotalLaps() const {
    return totalLaps_;
}

float CheckPointManager::GetCurrentLapTime() const {
    return clock_.getElapsedTime().asSeconds();
}

int CheckPointManager::GetCurrentCheckPointNumber() const {
    return currentCheckPoint_ + 1;
}

int CheckPointManager::GetTotalNumberOfCheckPoints() const {
    return (int) checkPoints_.size();
}

