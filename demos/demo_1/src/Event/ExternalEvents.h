/**
 * @defgroup external_events External events control
 */

/**
 *  @file
 *  @ingroup external_events
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _ExternalEvents_H_
#define _ExternalEvents_H_

#include <SFML/Window.hpp>  // Window handler
#include <EventManager.h>   // Event queue

/**
 * External events listener
 */
class ExternalEvents {
private:

public:
    /// @TODO ...
    ExternalEvents();

    /// @TODO ...
    ~ExternalEvents();

    /**
     * Poll external events and pass them to manager.
     * @param window
     * @param event_manager
     */
    void Listen(sf::Window &window, EventManager &event_manager);
};


#endif //_ExternalEvents_H_
