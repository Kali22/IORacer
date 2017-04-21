//
// Created by pawel on 04.04.17.
// Edited by j_ack on 13.04.17
//
#include <cassert>
#include <CheckPoint.h>
#include <CheckPointManager.h>

CheckPointManager::CheckPointManager(std::vector<CheckPointPtr> checkPoints, int totalLaps)
        : checkPoints_(checkPoints), currentLap_(1), currentSector_(0), totalLaps_(totalLaps) {
    assert(!checkPoints.empty());
    for (auto checkPoint : checkPoints) {
        checkPoint->SetObserver(this);
    }
    totalSectors_ = (int) checkPoints_.size();
    timeManager_ = std::make_shared<TimeManager>(currentSector_, currentLap_, totalSectors_);
    Reset();
}

void CheckPointManager::Reset() {
    GetCurrentCheckPoint()->SetEnable(false);
    currentSector_ = 0;
    currentLap_ = 1;
    GetCurrentCheckPoint()->SetEnable(true);
    timeManager_->Reset();
}

void CheckPointManager::NotifyCheckPointReached() {
    // CheckPoint reached? If reached, CheckPoint should be disabled.
    if (GetCurrentCheckPoint()->IsEnabled()) {
        return;
    }
    // Sector finished, register sector time
    timeManager_->BeginNewSector();
    currentSector_++;
    if (currentSector_ == totalSectors_) {
        // Lap finished, register lap time
        timeManager_->BeginNewLap();
        currentLap_++;
        currentSector_ = 0;
    }
    GetCurrentCheckPoint()->SetEnable(true);
}

void CheckPointManager::Draw(sf::RenderWindow *window) const {
    auto checkPoint = GetCurrentCheckPoint();
    checkPoint->Draw(window);
}

CheckPointPtr CheckPointManager::GetCurrentCheckPoint() const {
    return checkPoints_[currentSector_];
}

sf::Vector2f CheckPointManager::GetNextCheckPointPosition() const {
    return GetCurrentCheckPoint()->GetPosition();
}


int CheckPointManager::GetCurrentLapNumber() const {
    return currentLap_;
}

int CheckPointManager::GetTotalNumberOfLaps() const {
    return totalLaps_;
}

int CheckPointManager::GetTotalNumberOfSectors() const {
    return totalSectors_;
}

int CheckPointManager::GetCurrentSectorNumber() const {
    return currentSector_;
}

void CheckPointManager::Update() {
    timeManager_->Update();
}

TimeManagerPtr CheckPointManager::GetTimeManager() const {
    return timeManager_;
}

bool CheckPointManager::NewSectorBeginNotify() const {
    return (timeManager_->NewSectorBeginNotify()) && ((currentLap_ > 1) || (currentSector_ > 0));
}

bool CheckPointManager::NewLapBeginNotify() const {
    return (timeManager_->NewLapBeginNotify()) &&  (currentLap_ > 1);
}