/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 22.03.17
 */

#ifndef _EventManager_H_
#define _EventManager_H_

#include <vector>
#include <Event.h>
#include <SFML/Window/Event.hpp>


/**
 * Event Manager
 * Collects all events in queue.
 * Events can be processed further.
 */
class EventManager {
private:
    /// Event queue (circular buffer?)
    std::vector<Event> event_queue;
    /// Queue begin
    int begin;
    /// Queue end
    int end;

public:
    EventManager();

    ~EventManager();

    /// Add new event to the queue
    void PushEvent(const sf::Event &event);

    /// Take event and remove
    bool PopEvent(Event &event);
};


#endif //_EventManager_H_
