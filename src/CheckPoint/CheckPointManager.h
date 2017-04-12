#pragma once

#include <CheckPoint.h>
#include <CheckPointObserver.h>
#include <SFML/System/Clock.hpp>
#include <Drawable.h>

/**
 * Store list of chekpoints. Track and update active checkpoint.
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
    int GetCurrentCheckPointNumber() const;

    /**
     * Total # of checkpoints in lap.
     * @return # of checkpoints
     */
    int GetTotalNumberOfCheckPoints() const;

private:
    CheckPointPtr GetCurrentCheckPoint() const;

    std::vector<CheckPointPtr> checkPoints_;
    std::vector<std::vector<float> > lapTimes_;
    int finishedLap_;
    int totalLaps_;
    int currentCheckPoint_;
    sf::Clock clock_;
};

using CheckPointManagerPtr = std::shared_ptr<CheckPointManager>;
