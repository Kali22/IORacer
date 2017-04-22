#pragma once
/**
 *  @defgroup hud Head-Up Display
 *  Head-Up Display module.
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
#include <Entity/Container.h>

/**
 * Head-Up Display class.
 * @TODO is finite numeric test while getting time from CheckPointManager
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
     * @param option true = debug on, false = off.
     */
    void DebugDisplay(bool option);

    /**
     * Toggle debug display.
     */
    void DebugDisplayToggle();

private:
    void CreateSectorLapContainer();

    void CreateLapTimeContainer();

    void CreateSectorTimeContainer();

    void CreateNotifyContainer();

    /// Containers
    std::vector<ContainerPtr> containers_;

    /// HUD reference screen
    sf::View hudView_;

    bool showDebug_;

    /*-------- INDICATORS ----------*/
    ContainerPtr lapFinishIndicator_;
    ContainerPtr sectorFinishIndicator_;

    /// Vehicle pointer
    VehiclePtr vehicle_;
    /// Map pointer
    MapPtr map_;
    /// Checkpoint manager pointer
    CheckPointManagerPtr checkPointManager_;
};

using HUDPtr = std::shared_ptr<HUD>;
