/**
 *  @file
 *  @ingroup external_events
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include <ExternalEvents.h>
#include <EventManager.h>

ExternalEvents::ExternalEvents() {

}

ExternalEvents::~ExternalEvents() {

}

void ExternalEvents::Listen(sf::Window &window, EventManager &event_manager) {
    sf::Event event;
    // Fetch all events
    while (window.pollEvent(event)) {
        event_manager.PushEvent(event);
    }
}

