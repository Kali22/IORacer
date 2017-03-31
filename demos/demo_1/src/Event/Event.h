/**
 * @defgroup event Event
 * Application event structure
 */

/**
 *  @file
 *  @ingroup event
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 22.03.17
 */

#ifndef _Event_H_
#define _Event_H_

#include <EventTypes.h>

/**
 * Event package
 */
class Event {
public:
    event_type_t event_type;

    union event_param {
        int t1; // sth1
        int t2; // sth2
    };
};


#endif //_Event_H_
