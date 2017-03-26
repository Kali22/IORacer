/**
 *  @file
 *  @ingroup io_racer
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include <IORacer.h>

IORacer::IORacer() {

}


IORacer::~IORacer() {

}

void IORacer::ParseParams(int argc, char **argv) {

}

void IORacer::Initialize() {
    main_view.Initialize();
}

void IORacer::Run() {
    while (!IsOver()) {
        // Poll all events from user and OS and pass them to manager
        external_events.Listen(main_view.GetWindowHandler(), event_manager);
        // Propagate collected events to all contexts
        context_manager.ProcessEvents(event_manager);
        // Process all contexts, let them do a job
        context_manager.ProcessContexts(event_manager);
        // Print everything on the screen
        context_manager.RenderContexts(main_view.GetRendererHandler());
    }
}

int IORacer::Exit() {
    return 0;
}

bool IORacer::IsOver() {
    return true;
}
