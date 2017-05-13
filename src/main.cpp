/**
 *  @file
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  Main entry point.
 */

#include <bits/stdc++.h>
#include <Race.h>
#include <Menu.h>
#include <Drawable.h>
#include <ObjectManager.h>
#include <TextureManager.h>
#include <MapManager.h>
#include <CheckPoint.h>
#include <MathUtil.h>
#include <VehicleObject.h>

/**
 * Main. Entry point.
 * @param argc # of cmd line arguments
 * @param argv cmd line arguments
 * @return exit code
 */

RacePtr InitializeRace(b2World *world, RenderWindowPtr window,
                       CheckPointManagerPtr checkPointManager, MapPtr map,
                       ObjectManagerPtr objectManager) {
    /* Load map */
    HUDPtr hud = std::make_shared<HUD>(nullptr, map);

    const int scale = 30; // TODO remove in vehicle use case
    /* Set initial car params */
    CarParametersPtr carParameters = std::make_shared<CarParameters>();
    VehicleObjectPtr vehicleObject = std::dynamic_pointer_cast<VehicleObject>
            (objectManager->GetObjectInstanceByName("vehicle"));
    if (vehicleObject == nullptr) {
        std::cerr << "Failed to getting vehicle object.";
        exit(1);
    }
    sf::Vector2f pos = map->GetStartPosition();
    vehicleObject->SetPosition(pos.x, pos.y);
    vehicleObject->SetRotation(MathUtil::DegreeToRadian(90));

    VehiclePtr vehicle = std::make_shared<Vehicle>(carParameters,
                                                   vehicleObject);

    /* Initialize race */
    RacePtr race = std::make_shared<Race>(window, world, map, hud,
                                          checkPointManager);
    race->Initialize(vehicle);
    return race;
}

int main(int argc, char **argv) {
    /* Create world */
    b2World *world = new b2World(b2Vec2(0, 0));

    TextureManagerPtr textureManager = std::make_shared<TextureManager>();
    ObjectManagerPtr objectManager = std::make_shared<ObjectManager>
            (textureManager, world);
    MapManagerPtr mapManager = std::make_shared<MapManager>(textureManager,
                                                            objectManager);
    MapPtr map = mapManager->CreateMap("map_1");
    map->SetStartPosition(sf::Vector2f(4250, 3890)); // TODO read from conf

    /* Prepare the window */
    RenderWindowPtr window = std::make_shared<sf::RenderWindow>
            (sf::VideoMode::getDesktopMode(), "IORacer",
             sf::Style::Fullscreen);
    window->setFramerateLimit(60);

    const int totalLaps = 15; // TODO move to config file
    /* Set checkpoints */
    /// @TODO add race builder
    /// @TODO move checkPointsParser to map Load
    CheckPointManagerPtr checkPointManager =
            std::make_shared<CheckPointManager>(map->GetCheckpoints(),
                                                totalLaps);

    /* Initialize application */
    RacePtr race = InitializeRace(world, window, checkPointManager, map, objectManager);
    MenuPtr menu = std::make_shared<Menu>(window, race);

    menu->Run();

    free(world);
    return 0;
}
