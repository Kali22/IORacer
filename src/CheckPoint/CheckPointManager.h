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

private:
    CheckPointPtr GetCurrentCheckPoint() const;

    std::vector<CheckPointPtr> checkPoints_;
    int finishedLap_;
    int currentCheckPoint_;
    sf::Clock clock_;
};

using CheckPointManagerPtr = std::shared_ptr<CheckPointManager>;
