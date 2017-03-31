/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/27/17
 */

#include <EventClient.h>

void EventClient::RegisterEventType(event_type_t type) {
    registered_events.insert(type);
}

void EventClient::UnregisterEventType(event_type_t type) {
    registered_events.erase(type);
}

bool EventClient::GetEvent(Event &event) {
    return event_buffer.Get(event);
}

void EventClient::SendEvent(Event event) {
    PushEvent(event_server, event);
}

void EventClient::PushEvent(EventServer *server, Event event) {
    if (server != nullptr) {
        server->event_buffer.Add(event);
    }
}

void EventClient::SetServer(EventServer *server) {
    event_server = server;
}

