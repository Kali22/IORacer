#pragma once
/**
 *  @defgroup hud Head-Up Display
 *  Head-Up Display module.
 *
 *  @TODO Show: active lap
 *  @TODO Show: laps to go
 *  @TODO Show: best lap time
 *  @TODO Show: last lap time
 *  @TODO Show: elapsed time
 */

/**
 *  @file
 *  @ingroup hud
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <Drawable.h>
#include <Vehicle.h>
#include <Text.h>
#include <CheckPointManager.h>

/**
 * Head-Up Display class.
 */
class HUD : public Drawable {
public:
    /**
     * Create head-up display.
     * @TODO car param here is useless?
     * @param car
     * @param map
     */
    HUD(VehiclePtr car, MapPtr map);

    ~HUD();

    /**
     * Draw HUD on the screen.
     * @param window screen
     */
    void Draw(sf::RenderWindow *window) const;

    /**
     * Initialize HUD and bind vehicle.
     * @param vehicle vehicle
     */
    void Initialize(VehiclePtr vehicle, CheckPointManagerPtr checkPointManager);

    /**
     * Update HUD data.
     */
    void Update();

    /**
     * Enable/Disable gameplay debugger display.
     * @param option true = debug on, false = ow.
     */
    void DebugDisplay(bool option);

    /**
     * Toggle debug display.
     */
    void DebugDisplayToggle();

private:
    /// HUD reference screen
    sf::View hudView_;
    /// Show debug data flag
    bool showDebug_;
    /// SFML debugging data
    Text debugData_;

    /// Time labels
    Text timeLabels_;
    /// Timming data
    Text timeData_;

    /// Lap data labels
    Text lapLabels_;
    /// Lap data
    Text lapData_;

    /// Vehicle pointer
    VehiclePtr vehicle_;
    /// Map pointer
    MapPtr map_;
    /// Checkpoint manager pointer
    CheckPointManagerPtr checkPointManager_;

    /**
     * Print hud text background.
     * @param window render target
     * @param posX upper-left corner X pos
     * @param posy upper-left corner Y pos
     * @param sizeX x size
     * @param sizeY y size
     */
    void PrintBackBox(sf::RenderWindow *window, float posX, float posY, float sizeX, float sizeY) const;
};

using HUDPtr = std::shared_ptr<HUD>;
