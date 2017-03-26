/**
 *  @defgroup context_event
 *  Context event queue and filter
 */

/**
 *  @file
 *  @ingroup conext_event
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 22.03.17
 */

#ifndef _ContextEvents_H_
#define _ContextEvents_H_

#include <EventTypes.h>
#include <Event.h>
#include <vector>
#include <set>

class ContextEvents {
private:
    /// Events buffer
    std::vector<Event> queue;
    /// Registered events set
    std::set<event_type_t> registered_events;
public:
    /**
     * Create...
     */
    ContextEvents();

    /**
     * Destroy...
     */
    ~ContextEvents();

    /**
     * Add event if it was previously registered
     * @param event
     */
    void PushEvent(Event &event);

    /**
     * Take next event.
     * @return true if event queue not empty, false otherwise
     */
    bool PopEvent(Event &event);

    /**
     * Enable receiving events with given type.
     * @param type
     */
    void RegisterEventType(event_type_t type);

    /**
     * Disable receiving events with given type.
     * @param type
     */
    void UnregisterEventType(event_type_t type);
};


#endif //_ContextEvents_H_
