/**
 *  @file
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  Main entry ponit.
 */

#include <Race.hpp>

/**
 * Main. Entry point.
 * @param argc # of cmd line arguments
 * @param argv cmd line arguments
 * @return exit code
 */
int main(int argc, char **argv) {
    /** Prepare the window */
    sf::RenderWindow Window(sf::VideoMode(800, 1200, 32), "IORacer");
    Window.setFramerateLimit(60);
    Race race(Window);
    race.Run();

    return 0;
}