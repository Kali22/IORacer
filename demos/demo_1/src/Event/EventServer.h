/**
 *  @defgroup event_manager
 */

/**
 *  @file
 *  @ingroup event_manager
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 27.03.17
 */

#ifndef _EventServer_H_
#define _EventServer_H_

#include <set>
#include <SFML/Window.hpp>

#include <Events.h>
#include <EventBuffer.h>

/**
 * Event Server class
 * Usecase:
 *  - manage event passing between clients
 *  - manage external events sources
 */
class EventServer {
private:
    /// Events queued in buffer
    EventBuffer event_buffer;
    /// Set of external events sources
    std::set<sf::Window *> event_sources;
    /// Set of destination objects
    std::set<EventClient *> event_clients;

    friend class EventClient;

    /**
     * Translate and queue external event.
     * @param event external event
     */
    void AddExternalEvent(sf::Event event);

    /**
     * Push event into given client queue.
     * @param client
     * @param event
     */
    void PushEvent(EventClient *client, Event event);
public:

    /**
     * Create event server.
     */
    EventServer();

    /**
     * Destroy event server.
     */
    ~EventServer();

    /**
     * Register window as external events source.
     * @param window pointer to source
     */
    void RegisterWindow(sf::Window *window);

    /**
     * Remove window from sources.
     * @param window pointer to source
     */
    void UnregisterWindow(sf::Window *window);

    /**
     *  Register event client.
     * @param client
     */
    void RegisterClient(EventClient *client);

    /**
     * Remove event client.
     * @param client
     */
    void UnregisterClient(EventClient *client);

    /**
     * Listen for external events.
     */
    void Listen();

    /**
     * Process event stored in buffer.
     */
    void ProcessEvents();
};

#endif //_EventServer_H_