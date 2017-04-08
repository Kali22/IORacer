/**
 *  @file
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  Main entry point.
 */

#include <Race.h>
#include <Module/Menu.h>

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
    float scale = 30.0;
    MenuPtr menu = std::make_shared<Menu>(&window, scale);
    menu->run();
    return 0;
}