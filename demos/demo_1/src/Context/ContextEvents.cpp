/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 22.03.17
 */

#include <Event.h>
#include <EventTypes.h>
#include <ContextEvents.h>

ContextEvents::ContextEvents() {

}

ContextEvents::~ContextEvents() {

}

void ContextEvents::PushEvent(Event &event) {

}

bool ContextEvents::PopEvent(Event &event) {
    return false;
}

void ContextEvents::RegisterEventType(event_type_t type) {
    registered_events.insert(type);
}

void ContextEvents::UnregisterEventType(event_type_t type) {
    registered_events.erase(type);
}
