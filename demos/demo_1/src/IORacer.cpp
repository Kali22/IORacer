/**
 *  @file
 *  @ingroup io_racer
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include "IORacer.h"

/**
 * Create game.
 */
IORacer::IORacer() {
    settings = new Settings();
    view = new MainView();
    controller = new GameController();
    context_manager = new ContextManager();
}

/**
 *  Stub.
 */
IORacer::~IORacer() {

}

/**
 * Parse command line parameters and apply settings.
 * @param argc
 * @param argv
 */
void IORacer::ParseParams(int argc, char **argv) {

}

/**
 * Initialize game structures.
 */
void IORacer::Initialize() {
    view->Initialize();
}

/**
 * Run game main loop.
 */
void IORacer::Run() {
    while (!IsOver()) {
        // Poll all events from user and OS
        external_events.Listen(main_view, event_manager);
        // Propagate collected events to all contexts
        context_manager.PropagateEvents(event_manager);
        // Process all contexts, let them send event
        context_manager.ProcessContexts(event_manager);
        // Print everything on the screen
        MainView.Render(context_manager.GetContextsViews());
    }
}

/**
 * Perform cleaning and returns appropriate exit code.
 * @return exit code
 */
int IORacer::Exit() {
    return 0;
}

/**
 * Check whether game is over.
 * @return true if program is over, false otherwise
 */
bool IORacer::IsOver() {
    return false;
}
