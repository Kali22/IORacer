/**
 *  @defgroup io_racer IORacer
 *  IORacer game main class.
 *  @TODO Think about passing events to main class.... Event buffers should me more general!?
 */

/**
 *  @file
 *  @ingroup io_racer
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _IORacer_H_
#define _IORacer_H_

#include <MainView.h>
#include <EventServer.h>
#include <EventClient.h>
#include <ContextManager.h>

/**
 * Main game object.
 */
class IORacer {
private:
    /// Context manager
    ContextManager context_manager;

    /// Event server
    EventServer event_server;
    /// Main window manager and renderer
    MainView main_view;

    /**
     *  Event client
     *  Handling core events
     */
    EventClient event_client;

    /// Close application
    bool game_over;

    /**
     * Check whether game is over.
     * @return true if program is over, false otherwise
     */
    bool IsOver();

    /**
     * Process all events for main management unit.
     */
    void ProcessReceivedEvents();
public:

    /**
     * Create game.
     */
    IORacer();

    /**
     *  Stub.
     */
    ~IORacer();

    /**
     * Parse command line parameters and apply settings.
     * @param argc
     * @param argv
     */
    void ParseParams(int argc, char **argv);

    /**
     * Initialize game structures.
     */
    void Initialize();

    /**
     * Run game main loop.
     */
    void Run();

    /**
     * Perform cleaning and returns appropriate exit code.
     * @return exit code
     */
    int Exit();
};


#endif //_IORacer_H_
