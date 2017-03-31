/**
 *  @file
 *  @ingroup event_server
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 22.03.17
 */

#include <EventServer.h>
#include <EventClient.h>

EventServer::EventServer() {

}

EventServer::~EventServer() {

}

void EventServer::RegisterWindow(sf::Window *window) {
    event_sources.insert(window);
}

void EventServer::UnregisterWindow(sf::Window *window) {
    event_sources.erase(window);
}

void EventServer::RegisterClient(EventClient *client) {
    event_clients.insert(client);
    client->SetServer(this);
}

void EventServer::UnregisterClient(EventClient *client) {
    event_clients.erase(client);
    client->SetServer(NULL);
}

void EventServer::Listen() {
    sf::Event event;

    // Get first source in set.
    std::set<sf::Window *>::iterator it = event_sources.begin();
    // Iterate over whole set of sources
    while (it != event_sources.end()) {
        sf::Window *window = *it;
        // Fetch all events
        while (window->pollEvent(event)) {
            printf("External event caugth: %d\n", (int) event.type);
            // Translate and add to main event queue
            AddExternalEvent(event);
        }
    }
}

void EventServer::ProcessEvents() {
    Event event;
    printf("PRocess!\n");
    while (event_buffer.Get(event)) {
        printf("Processing event: %d\n", (int) event.event_type);
        std::set<EventClient *>::iterator it = event_clients.begin();
        while (it != event_clients.end()) {
            // Push event into given client queue
            PushEvent(*it, event);
        }
    }
}

void EventServer::AddExternalEvent(sf::Event event) {
    Event e;
    e.event_type = (event_type_t) event.type;
    event_buffer.Add(e);
}

void EventServer::PushEvent(EventClient *client, Event event) {
    // Event type matched
    if (client->registered_events.find(event.event_type) != client->registered_events.end()) {
        client->event_buffer.Add(event);
    }
}