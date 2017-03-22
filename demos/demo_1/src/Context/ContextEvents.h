/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 22.03.17
 */

#ifndef _ContextEvents_H_
#define _ContextEvents_H_

#include <vector>
#include <set>

class ContextEvents {
private:
    std::vector<Event>;
    std::set<event_type_t> registered_events;
public:
    /**
     * Add event if it was previously registered
     * @param event
     */
    void PushEvent(ContextEvents &event);

    /**
     * Take next event.
     * @return
     */
    bool PopEvent(Event &event);

    /**
     * Enable receiving events with given type.
     * @param type
     */
    void RegisterEventType(event_type_t type);

    /**
     * Enable receiving events with given type.
     * @param type
     */
    void UnregisterEventType(event_type_t type);
};


#endif //_ContextEvents_H_
