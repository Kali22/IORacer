//
// Created by pawel on 04.04.17.
// Edited by j_ack on 13.04.17
//
#include <cassert>
#include <CheckPoint.h>
#include <CheckPointManager.h>

CheckPointManager::CheckPointManager(std::vector<CheckPointPtr> checkPoints)
        : checkPoints_(checkPoints), currentLap_(1), currentSector_(1) {
    assert(!checkPoints.empty());
    for (auto checkPoint : checkPoints) {
        checkPoint->SetObserver(this);
    }
    Reset();
}

void CheckPointManager::Reset() {
    GetCurrentCheckPoint()->SetEnable(false);
    currentSector_ = 1;
    currentLap_ = 1;
    GetCurrentCheckPoint()->SetEnable(true);
    lapClock_.restart();
    sectorClock_.restart();

    /// @TODO ???? End of race conditions?
    totalLaps_ = 100;
    totalSectors_ = (int) checkPoints_.size();

    accmulativeSectorsTimes_.push_back(std::vector<float>(totalSectors_ + 1, 0.0));
    accmulativeSectorsTimes_.push_back(std::vector<float>(1, 0.0));

    // No lap finished
    bestLapTimeNumber_ = 0;
    bestLapTime_ = lapTimeLimit_;
    bestSectorTimeNumber_ = std::vector<int>(totalSectors_ + 1, 0);
    bestSectorTime_ = std::vector<float>(totalSectors_ + 1, lapTimeLimit_);
    bestSectorTime_[0] = 0.f;
}

sf::Time CheckPointManager::GetElapsedTime() const {
    return lapClock_.getElapsedTime();
}

void CheckPointManager::NotifyCheckPointReached() {
    if (GetCurrentCheckPoint()->IsEnabled()) {
        return;
    }
    accmulativeSectorsTimes_[currentLap_].push_back(lapClock_.getElapsedTime().asSeconds());
    float currentSectorTime = accmulativeSectorsTimes_[currentLap_][currentSector_] -
                              accmulativeSectorsTimes_[currentLap_][currentSector_ - 1];
    if (currentSectorTime < bestSectorTime_[currentSector_]) {
        bestSectorTime_[currentSector_] = currentSectorTime;
        bestSectorTimeNumber_[currentSector_] = currentLap_;
    }
    currentSector_++;
    sectorClock_.restart();
    if (currentSector_ > totalSectors_) {
        if (accmulativeSectorsTimes_[currentLap_][totalSectors_] < bestLapTime_) {
            bestLapTime_ = accmulativeSectorsTimes_[currentLap_][totalSectors_];
            bestLapTimeNumber_ = currentLap_;
        }
        accmulativeSectorsTimes_.push_back(std::vector<float>(1, 0.0));
        currentLap_++;
        currentSector_ = 1;
        lapClock_.restart();
    }
    GetCurrentCheckPoint()->SetEnable(true);
}

void CheckPointManager::Draw(sf::RenderWindow *window) const {
    auto checkPoint = GetCurrentCheckPoint();
    checkPoint->Draw(window);
}

CheckPointPtr CheckPointManager::GetCurrentCheckPoint() const {
    return checkPoints_[currentSector_ - 1];
}

sf::Vector2f CheckPointManager::GetNextCheckPointPosition() const {
    return GetCurrentCheckPoint()->GetPosition();
}

float CheckPointManager::GetLastLapTime() const {
    if (currentLap_ > 1) {
        return accmulativeSectorsTimes_[currentLap_ - 1][totalSectors_];
    } else {
        return lapTimeLimit_;
    }
}

float CheckPointManager::GetBestLapTime() const {
    return bestLapTime_;
}

int CheckPointManager::GetCurrentLap() const {
    return currentLap_;
}

int CheckPointManager::GetTotalLaps() const {
    return totalLaps_;
}

float CheckPointManager::GetCurrentLapTime() const {
    return lapClock_.getElapsedTime().asSeconds();
}

int CheckPointManager::GetCurrentSectorNumber() const {
    return currentSector_;
}

int CheckPointManager::GetTotalNumberOfSectors() const {
    return (int) totalSectors_;
}

bool CheckPointManager::IsSectorFinished() const {
    return (sectorFinishIndicatorTime > sectorClock_.getElapsedTime().asSeconds()) &&
           ((currentLap_ > 1) || (currentSector_ > 1));
}

bool CheckPointManager::IsLapFinished() const {
    return (lapClock_.getElapsedTime().asSeconds() < lapFinishIndicatorTime) && (currentLap_ > 1);
}

float CheckPointManager::GetLastSectorTime() const {
    float time;
    if (currentSector_ > 1) {
        time = accmulativeSectorsTimes_[currentLap_][currentSector_ - 1] -
               accmulativeSectorsTimes_[currentLap_][currentSector_ - 2];
    } else {
        time = accmulativeSectorsTimes_[currentLap_ - 1][totalSectors_] -
               accmulativeSectorsTimes_[currentLap_ - 1][totalSectors_ - 1];
    }
    return time;
}

