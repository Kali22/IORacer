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
    void CreateSectorLapContainer(sf::FloatRect frame);

    void CreateLapTimeContainer(sf::FloatRect frame);

    void CreateSectorTimeContainer(sf::FloatRect frame);

    void CreateNotifyContainer(sf::FloatRect lapFrame, sf::FloatRect sectorFrame);

    void AddContainerTitle(ContainerPtr container, std::string title);

    void AddTimeIndicator(ContainerPtr container, std::string title, const float &data, sf::IntRect grid);

    void AddTimeIndicatorWithoutTitle(ContainerPtr container, const float &data, sf::IntRect grid, float fontSize);

    void AddIntegerIndicator(ContainerPtr container, std::string title, const int &data, int limit, sf::IntRect grid);

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

    void DrawMinimap(sf::RenderWindow *window) const;

    void DrawMinimapBackground(sf::RenderWindow *window, const sf::Vector2u &windowSize) const;

    void DrawMinimapVehicle(sf::RenderWindow *window, const sf::Vector2f &mapSize, float beginX, float beginY) const;

    void DrawMinimapCheckpoint(sf::RenderWindow *window, const sf::Vector2f &mapSize, float beginX, float beginY) const;
};

using HUDPtr = std::shared_ptr<HUD>;
