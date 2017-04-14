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

    /// @TODO ???? End of race conditions?
    totalLaps_ = 100;
    totalSectors_ = (int) checkPoints_.size();

    // No lap finished
    combinedBestTime_ = 0;
    bestLapTimeNumber_ = 0;
    bestLapTime_ = 0;
    lapClock_.restart();
    sectorClock_.restart();

    accumulativeSectorsTimes_.clear();
    sectorsTimes_.clear();
    bestSectorTimeNumber_.clear();
    bestSectorTime_.clear();
    bestSectorTimeNumber_ = std::vector<int>(totalSectors_ + 1, 0);
    bestSectorTime_ = std::vector<float>(totalSectors_ + 1, 0);
    // Add zeros in 'guard' zero lap
    accumulativeSectorsTimes_.push_back(std::vector<float>(totalSectors_ + 1, 0.0));
    sectorsTimes_.push_back(std::vector<float>(totalSectors_ + 1, 0.0));
    // Add guards in current lap
    accumulativeSectorsTimes_.push_back(std::vector<float>(1, 0.0));
    sectorsTimes_.push_back(std::vector<float>(1, 0.0));
    assert(accumulativeSectorsTimes_.size() == 2);
    assert(sectorsTimes_.size() == 2);
}

sf::Time CheckPointManager::GetElapsedTime() const {
    return lapClock_.getElapsedTime();
}

void CheckPointManager::NotifyCheckPointReached() {
    // CheckPoint reached?
    if (GetCurrentCheckPoint()->IsEnabled()) {
        return;
    }
    // Sector finished, register times
    float sectorTime = sectorClock_.getElapsedTime().asSeconds();
    float lapTime = lapClock_.getElapsedTime().asSeconds();
    sectorsTimes_[currentLap_].push_back(sectorTime);
    accumulativeSectorsTimes_[currentLap_].push_back(lapTime);
    sectorClock_.restart();

    // Check best sector time
    if ((sectorTime < bestSectorTime_[currentSector_]) || (bestSectorTime_[currentSector_] == 0.f)) {
        bestSectorTime_[currentSector_] = sectorTime;
        bestSectorTimeNumber_[currentSector_] = currentLap_;
    }

    currentSector_++;
    if (currentSector_ > totalSectors_) {
        // Check best lap time
        if ((lapTime < bestLapTime_) || (bestLapTime_ == 0.f)) {
            bestLapTime_ = lapTime;
            bestLapTimeNumber_ = currentLap_;
        }
        // Recalculate combined best lap time
        combinedBestTime_ = 0;
        for (auto t : bestSectorTime_)
            combinedBestTime_+= t;

        currentLap_++;
        currentSector_ = 1;
        lapClock_.restart();
        // Add new vector of times with guard
        accumulativeSectorsTimes_.push_back(std::vector<float>(1, 0.0));
        sectorsTimes_.push_back(std::vector<float>(1, 0.0));
        assert(accumulativeSectorsTimes_.size() == currentLap_ + 1);
        assert(sectorsTimes_.size() == currentLap_ + 1);
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
        return accumulativeSectorsTimes_[currentLap_ - 1][totalSectors_];
    } else {
        return 0.f;
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
    return (sectorClock_.getElapsedTime().asSeconds() < sectorFinishIndicatorTime) &&
           ((currentLap_ > 1) || (currentSector_ > 1));
}

bool CheckPointManager::IsLapFinished() const {
    return (lapClock_.getElapsedTime().asSeconds() < lapFinishIndicatorTime) && (currentLap_ > 1);
}

float CheckPointManager::GetPreviousSectorTime() const {
    return (currentSector_ > 1 ?
            sectorsTimes_[currentLap_][currentSector_ - 1] :
            sectorsTimes_[currentLap_ - 1][totalSectors_]);
}

int CheckPointManager::GetBestLapNumber() const {
    return bestLapTimeNumber_;
}

float CheckPointManager::GetCurrentSectorTime() const {
    return sectorClock_.getElapsedTime().asSeconds();
}

float CheckPointManager::GetLastSectorTime() const {
    return sectorsTimes_[currentLap_ - 1][currentSector_];
}

float CheckPointManager::GetBestSectorTime() const {
    return bestSectorTime_[currentSector_];
}

int CheckPointManager::GetBestSectorLapNumber() const {
    return bestSectorTimeNumber_[currentSector_];
}

float CheckPointManager::GetCombinedBestTime() const {
    return combinedBestTime_;
}

