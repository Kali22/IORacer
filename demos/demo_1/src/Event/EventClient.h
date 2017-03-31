/**
 *  @file
 *  @ingroup event_client
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/27/17
 */

#ifndef _EventClient_H_
#define _EventClient_H_

#include <set>

#include <Events.h>
#include <Event.h>
#include <EventBuffer.h>
#include <EventServer.h>

/**
 * Event client class.
 * Message passing interface.
 * Usecase:
 *  - Event reception from server.
 *  - Event broadcasting between clients
 *  - Event filtering
 */
class EventClient {
private:
    /// Outgoing events server
    EventServer *event_server;
    /// Incoming messages
    EventBuffer event_buffer;
    /// Registered events types
    std::set<event_type_t> registered_events;

    friend class EventServer;

    /**
     * Push event into server queue.
     * @param server
     * @param event
     */
    void PushEvent(EventServer *server, Event event);

    /**
     * Set event server pointer.
     * @param server
     */
    void SetServer(EventServer *server);
public:
    //----------------------  CONTEXT INTERFACE

    /**
     * Get incoming event from input event.
     * @param event
     * @return
     */
    bool GetEvent(Event &event);

    /**
     * Send event to server for broadcast.
     * @param event
     */
    void SendEvent(Event event);

    //----------------------  FILTERING TYPES
    /**
     * Select incoming types.
     * @param type
     */
    void RegisterEventType(event_type_t type);

    /**
     * Remove incoming types.
     * @param type
     */
    void UnregisterEventType(event_type_t type);
    //----------------------  END OF FILTERING TYPES


};


#endif //EventClient
