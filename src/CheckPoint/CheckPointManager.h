#pragma once

#include <CheckPoint.h>
#include <CheckPointObserver.h>
#include <SFML/System/Clock.hpp>
#include <Drawable.h>

/**
 * Store list of chekpoints. Track and update active checkpoint.
 * @TODO Check and fix laps counting
 */
class CheckPointManager : public CheckPointObserver, public Drawable {
public:
    CheckPointManager(std::vector<CheckPointPtr> checkPoints);

    /**
     * Reset active checkpoint to first on the list.
     */
    void Reset();

    sf::Time GetElapsedTime() const;

    /**
     * When function is called move active checkpoint indext to next checkpoint
     * if current active checkpoint was already set to disabled.
     * Call SetEnable(true) on new active checkpoint.
     */
    void NotifyCheckPointReached();

    /**
     * Draw active checkpoint.
     */
    void Draw(sf::RenderWindow *window) const;

    /**
     * Return next checkpoint coordinates.
     * @return checkpoint position
     */
    sf::Vector2f GetNextCheckPointPosition() const;

    /**
     * Returns current lap time.
     * Time elapsed from crossing first checkpoint.
     * @return time in seconds, -1.0 if unavailable
     */
    float GetCurrentLapTime() const;

    /**
     * Returns last lap time.
     * @return time in seconds, -1.0 if unavailable
     */
    float GetLastLapTime() const;

    /**
     * Returns best lap time.
     * @return time in seconds, -1.0 if unavailable
     */
    float GetBestLapTime() const;

    /**
     * Returns current lap.
     * @return current lap number
     */
    int GetCurrentLap() const;

    /**
     * Total number of laps in race
     * @return # of laps
     */
    int GetTotalLaps() const;

    /**
     * Returns id of recently crossed checkpoint.
     * @return id of recent checkpoint
     */
    int GetCurrentSectorNumber() const;

    /**
     * Total # of checkpoints in lap.
     * @return # of checkpoints
     */
    int GetTotalNumberOfSectors() const;

    /**
     * Chceck whether new lap begin.
     * @return true for some time after crossing start/meta line
     */
    bool IsLapFinished() const;

    /**
     * Chceck whether new sector begin.
     * @return true for some time after reaching checkpoint
     */
    bool IsSectorFinished() const;

    /**
     * Returns time in recent sector.
     * @return time in recent sector in seconds
     */
    float GetLastSectorTime() const;

private:
    CheckPointPtr GetCurrentCheckPoint() const;

    std::vector<CheckPointPtr> checkPoints_;

    /// Lap time max value
    const float lapTimeLimit_ = 5999.f;

    /// Current lap wall clock
    sf::Clock lapClock_;
    /// Current sector wall clock
    sf::Clock sectorClock_;

    /// Accumulative sectors times in each lap
    std::vector<std::vector<float> > accmulativeSectorsTimes_;
    /// Current sector number
    int currentSector_;
    /// Total number of track's sectors
    unsigned int totalSectors_;
    /// Current lap number
    int currentLap_;
    /// Total number of laps in race
    unsigned int totalLaps_;

    /// Number of lap with best time
    int bestLapTimeNumber_;
    /// Best lap time ever :)
    float bestLapTime_;
    /// Number of lap with best time in given sector
    std::vector<int> bestSectorTimeNumber_;
    /// Best time in given sector
    std::vector<float> bestSectorTime_;

    /// Lap finished notification duration in seconds.
    const float lapFinishIndicatorTime = 5.f;
    /// Sector finished notification duration in seconds.
    const float sectorFinishIndicatorTime = 2.f;
};

using CheckPointManagerPtr = std::shared_ptr<CheckPointManager>;
