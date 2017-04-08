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
int main(int argc, char **argv) {
    /* Prepare the window */
    sf::RenderWindow window(sf::VideoMode(1200, 800, 32), "IORacer");
    window.setFramerateLimit(60);
    float scale = 30;
    b2World *world = new b2World(b2Vec2(0, 0));
    MapPtr map = std::make_shared<Map>(world, scale, sf::Vector2f(4800, 3890));
    map->LoadMap("map_0", "Mapa testowa");

    // Set initiial car params

    HUDPtr hud = std::make_shared<HUD>(nullptr, map);
    /// TODO add race builder
    CheckPointParser parser(world, 30); // scale
    /// @TODO move checkPointsParser to map Load
    std::vector<CheckPointPtr> checkPoints = parser.ParseFile("../resource/maps/map_0/checkpoints_list");

    CheckPointManagerPtr checkPointManager = std::make_shared<CheckPointManager>(checkPoints);
    RacePtr race = std::make_shared<Race>(&window, world, map, hud, checkPointManager);
    CarParametersPtr carParameters = std::make_shared<CarParameters>();
    VehiclePtr vehicle = std::make_shared<Vehicle>(carParameters, scale);

    race->Initialize(vehicle);

    MenuPtr menu = std::make_shared<Menu>(&window, race);
    menu->run();
    return 0;
}