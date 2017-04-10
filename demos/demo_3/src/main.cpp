/**
 *  @file
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  Main entry ponit.
 */

#include <Race.h>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <Vehicle.h>
#include <Tools/Map.h>
#include <CheckPointManager.h>
#include <Tools/HUD.h>
#include <CheckPointParser.h>
#include <CarParams.h>

/**
 * Main. Entry point.
 * @param argc # of cmd line arguments
 * @param argv cmd line arguments
 * @return exit code
 */
int main(int argc, char **argv) {
    /* Prepare the window */
    sf::RenderWindow* window =
            new sf::RenderWindow(sf::VideoMode(1200, 800, 32), "IORacer");
    window->setFramerateLimit(60);
    b2World* world = new b2World(b2Vec2(0, 0));
    Map* map = new Map(world);
    map->LoadMap("map_0", "Mapa testowa");

    CarParameters carParameters;
    // Set initiial car params
    carParameters.activeTireModifier = 1.0f;
    carParameters.baseTireFriction = 1.0f;
    carParameters.maxBackwardSpeed = -20.f;
    carParameters.maxForwardSpeed = 60.f;
    carParameters.maxEnginePower = 30.f;
    carParameters.maxSteeringAngle = 20.f;
    carParameters.steeringSpeed = 120.0;

    Vehicle* vehicle = new Vehicle(carParameters);
    HUD* hud = new HUD(vehicle, map);
    /// TODO add race builder
    CheckPointParser parser(world, 30); // scale
    /// @TODO move checkPointsParser to map Load
    std::vector < CheckPoint * > checkPoints = parser.ParseFile(
            "../resource/maps/map_0/checkpoints_list");
    CheckPointManager* checkPointManager = new CheckPointManager(checkPoints);

    Race race(window, world, map, vehicle, hud, checkPointManager);
    race.Run();
    return 0;
}