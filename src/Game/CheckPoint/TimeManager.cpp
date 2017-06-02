#include <TimeManager.h>

TimeManager::TimeManager(const int &currentSector, const int &currentLap,
                         const int &totalSectors) :
        currentLap_(currentLap),
        currentSector_(currentSector),
        totalSectors_(totalSectors) {
    Reset();
    Update(0);
}

void TimeManager::Update(float dt) {
    lapClock_ += dt;
    sectorClock_ += dt;
    UpdateTimes();
    currentLapIndicator_ = currentLap_;
    currentSectorIndicator_ = currentSector_ + 1;
}

void TimeManager::Reset() {
    // No lap finished
    combinedBestLapTime_ = std::numeric_limits<float>::infinity();
    bestLapTime_ = std::numeric_limits<float>::infinity();
    bestLapNumber_ = 0;

    bestSectorTimeNumber_ = std::vector<int>((unsigned) totalSectors_, 0);
    bestSectorTimes_ = std::vector<float>((unsigned) totalSectors_,
                                          std::numeric_limits<float>::infinity());
    // Add zeros in 'guard' zero lap
    accumulativeSectorsTimes_ = {
            std::vector<float>((unsigned) totalSectors_,
                               std::numeric_limits<float>::infinity()),
            std::vector<float>()};
    sectorsTimes_ = accumulativeSectorsTimes_;
    StartClock();
}

void TimeManager::BeginNewSector() {
    float sectorTime = sectorClock_;
    sectorClock_ = 0;
    float lapTime = lapClock_;
    sectorsTimes_[currentLap_].push_back(sectorTime);
    accumulativeSectorsTimes_[currentLap_].push_back(lapTime);

    // Check best sector time
    if (sectorTime < bestSectorTimes_[currentSector_]) {
        bestSectorTimes_[currentSector_] = sectorTime;
        bestSectorTimeNumber_[currentSector_] = currentLap_;
    }
}

void TimeManager::BeginNewLap() {
    float lapTime = lapClock_;
    lapClock_ = 0;
    if (lapTime < bestLapTime_) {
        bestLapTime_ = lapTime;
        bestLapNumber_ = currentLap_;
    }

    // Recalculate combined best lap time
    combinedBestLapTime_ = 0;
    for (auto sectorTime : bestSectorTimes_) {
        combinedBestLapTime_ += sectorTime;
    }

    accumulativeSectorsTimes_.push_back(std::vector<float>());
    sectorsTimes_.push_back(std::vector<float>());
}

void TimeManager::StartClock() {
    sectorClock_ = 0;
    lapClock_ = 0;
}

bool TimeManager::NewLapBeginNotify() const {
    return currentLapTime_ < lapFinishIndicatorTimeout_;
}

bool TimeManager::NewSectorBeginNotify() const {
    return currentSectorTime_ < sectorFinishIndicatorTimeout_;
}

const float &TimeManager::GetCurrentLapTime() const {
    return currentLapTime_;
}

const float &TimeManager::GetLastLapTime() const {
    return lastLapTime_;
}

const float &TimeManager::GetBestLapTime() const {
    return bestLapTime_;
}

const float &TimeManager::GetCombinedBestLapTime() const {
    return combinedBestLapTime_;
}

const float &TimeManager::GetCurrentSectorTime() const {
    return currentSectorTime_;
}

const float &TimeManager::GetLastSectorTime() const {
    return lastSectorTime_;
}

const float &TimeManager::GetBestSectorTime() const {
    return bestSectorTime_;
}

const float &TimeManager::GetPreviousSectorTime() const {
    return previousSectorTime_;
}

const int &TimeManager::GetBestSectorLapNumber() const {
    return bestSectorLapNumber_;
}

const int &TimeManager::GetBestLapNumber() const {
    return bestLapNumber_;
}

const int &TimeManager::GetCurrentLapNumber() const {
    return currentLapIndicator_;
}

const int &TimeManager::GetCurrentSectorNumber() const {
    return currentSectorIndicator_;
}

void TimeManager::UpdateTimes() {
    currentSectorTime_ = sectorClock_;
    lastSectorTime_ = sectorsTimes_[currentLap_ - 1][currentSector_];
    bestSectorTime_ = bestSectorTimes_[currentSector_];
    bestSectorLapNumber_ = bestSectorTimeNumber_[currentSector_];
    UpdatePartialTimers();
}

void TimeManager::UpdatePartialTimers() {
    if (currentSector_ > 0) {
        previousSectorTime_ = sectorsTimes_[currentLap_][currentSector_ - 1];
    } else {
        previousSectorTime_ = sectorsTimes_[currentLap_ - 1][totalSectors_ - 1];
    }

    currentLapTime_ = lapClock_;
    if (currentLap_ > 1) {
        lastLapTime_ =
                accumulativeSectorsTimes_[currentLap_ - 1][totalSectors_ - 1];
    } else {
        lastLapTime_ = std::numeric_limits<float>::infinity();
    }
}
