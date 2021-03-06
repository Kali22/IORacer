#pragma once


#include <SFML/System/Clock.hpp>
#include <bits/stdc++.h>
#include <Updatable.h>

/**
 * Race time management.
 */
class TimeManager {
public:
    TimeManager(const int &currentSector, const int &currentLap,
                const int &totalSectors);

    void Update(float dt);

    void Reset();

    void BeginNewSector();

    void BeginNewLap();

    void StartClock();

    bool NewLapBeginNotify() const;

    bool NewSectorBeginNotify() const;

    /*------- TIMING DATA INDICATORS ------*/
    const float &GetCurrentLapTime() const;

    const float &GetLastLapTime() const;

    const float &GetBestLapTime() const;

    const float &GetCombinedBestLapTime() const;

    const float &GetCurrentSectorTime() const;

    const float &GetLastSectorTime() const;

    const float &GetBestSectorTime() const;

    const float &GetPreviousSectorTime() const;

    const int &GetBestSectorLapNumber() const;

    const int &GetBestLapNumber() const;

    const int &GetCurrentLapNumber() const;

    const int &GetCurrentSectorNumber() const;

private:
    void UpdateTimes();

    void UpdatePartialTimers();

    /// Current lap wall clock
    float lapClock_;
    /// Current sector wall clock
    float sectorClock_;

    /// Accumulative sectors times in each lap
    std::vector<std::vector<float> > accumulativeSectorsTimes_;
    /// Sector times
    std::vector<std::vector<float> > sectorsTimes_;

    /// Number of lap with best time in given sector
    std::vector<int> bestSectorTimeNumber_;
    /// Best time in given sector
    std::vector<float> bestSectorTimes_;

    const int &currentSector_;
    const int &currentLap_;
    const int &totalSectors_;

    /// Lap finished notification duration in seconds.
    const float lapFinishIndicatorTimeout_ = 4.f;
    /// Sector finished notification duration in seconds.
    const float sectorFinishIndicatorTimeout_ = 2.f;

    /*------- TIMING DATA INDICATORS ------*/
    float currentLapTime_;
    float lastLapTime_;
    float bestLapTime_;
    float combinedBestLapTime_;
    float currentSectorTime_;

    float lastSectorTime_;
    float bestSectorTime_;
    float previousSectorTime_;

    int bestSectorLapNumber_;
    int bestLapNumber_;
    int currentSectorIndicator_;
    int currentLapIndicator_;
};

using TimeManagerPtr = std::shared_ptr<TimeManager>;
