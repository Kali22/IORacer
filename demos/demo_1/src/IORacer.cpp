/**
 *  @file
 *  @ingroup io_racer
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include <IORacer.h>
#include <cstdio>

IORacer::IORacer() {
    printf("IORacer init!\n");
}

IORacer::~IORacer() {
    printf("IORacer close!\n");
}

void IORacer::ParseParams(int argc, char **argv) {
    printf("Parsing command line params!\n");
}

void IORacer::Initialize() {
    printf("IORacer initialization!\n");
    // We wanna play!
    game_over = false;

    // Init main window
    main_view.Initialize();
    // Bind window as event source
    event_server.RegisterWindow(main_view.GetWindowHandler());
    // Bind event client
    event_server.RegisterClient(&event_client);

    event_client.RegisterEventType((event_type_t) sf::Event::Closed);
}

void IORacer::Run() {
    while (!IsOver()) {
        // Listen for external events
        event_server.Listen();
        // Process all collected events
        event_server.ProcessEvents();
        // Check whether events arrived to main unit
        ProcessReceivedEvents();

        // Process contexts

        // Render contexts
    }
}

int IORacer::Exit() {
    printf("IORacer exit!\n");
    event_server.UnregisterWindow(main_view.GetWindowHandler());
    event_server.UnregisterClient(&event_client);

    return 0;
}

bool IORacer::IsOver() {
    return game_over;
}

void IORacer::ProcessReceivedEvents() {
    Event event;
    while (event_client.GetEvent(event)) {
        printf("IORacer - process event: %d\n", event.event_type);
        /// @TODO Here you can put stuff controlling your main
        switch (event.event_type) {
            case 0:
                game_over = true;
                main_view.GetWindowHandler()->close();
                break;
        }
    }
}
