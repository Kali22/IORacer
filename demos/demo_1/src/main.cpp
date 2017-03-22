/**
 *  @file
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  Main entry ponit.
 */

#include <IORacer.h>

/**
 * Main. Entry point.
 * @param argc # of cmd line arguments
 * @param argv cmd line arguments
 * @return exit code
 */
int main(int argc, char **argv) {
    IORacer game;   // Create game object
    game.ParseParams(argc, argv); // Pass command line parameters
    game.Initialize(); // Initialize game
    game.Run(); // Play the game
    return game.Exit(); // Finish game cycle and return exit status code
}