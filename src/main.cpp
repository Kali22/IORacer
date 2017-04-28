/**
 *  @file
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  Main entry point.
 */

#include <Race.h>
#include <Module/Menu.h>
#include <CheckPointParser.h>

/**
 * Main. Entry point.
 * @param argc # of cmd line arguments
 * @param argv cmd line arguments
 * @return exit code
 */

CheckPointManagerPtr SetCheckpoints(b2World *world) {
    /// @TODO add race builder
    /// @TODO move checkPointsParser to map Load
    CheckPointParser parser(world, 30); // scale
    std::vector<CheckPointPtr> checkPoints = parser.ParseFile("../resource/maps/map_0/checkpoints_list");
    CheckPointManagerPtr checkPointManager = std::make_shared<CheckPointManager>(checkPoints, 15);
    return checkPointManager;
}

RacePtr InitializeRace(b2World *world, float scale, sf::RenderWindow &window) {
    /* Set checkpoints */
    CheckPointManagerPtr checkPointManager = SetCheckpoints(world);

    /* Load map */
    MapPtr map = std::make_shared<Map>(world, scale, sf::Vector2f(4250, 3890));
    map->LoadMap("map_0", "Mapa testowa");
    HUDPtr hud = std::make_shared<HUD>(nullptr, map);

    /* Set initial car params */
    CarParametersPtr carParameters = std::make_shared<CarParameters>();
    VehiclePtr vehicle = std::make_shared<Vehicle>(carParameters, scale);

    /* Initialize race */
    RacePtr race = std::make_shared<Race>(&window, world, map, hud, checkPointManager);
    race->Initialize(vehicle);

    return race;
}

int main(int argc, char **argv) {
    /* Prepare the window */
    sf::RenderWindow window(sf::VideoMode(1200, 800, 32), "IORacer");
    window.setFramerateLimit(60);
    float scale = 30;

    /* Create world */
    b2World *world = new b2World(b2Vec2(0, 0));

    /* Initialize application */
    RacePtr race = InitializeRace(world, scale, window);
    MenuPtr menu = std::make_shared<Menu>(&window, race);

    menu->Run();

    free(world);
    return 0;
}
