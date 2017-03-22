/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _ContextManager_H_
#define _ContextManager_H_

#include <Context.h>
#include <EventManager.h>
#include <vector>

class ContextManager {
private:
    std::vector<Context> context_list;
public:
    ContextManager();

    ~ContextManager();

    /**
     * Propagate collected events to contexts.
     * @param event_manager
     */
    void PropagateEvents(EventManager &event_manager);

    /**
     * Process all events and let them create events.
     * @param event_manager
     */
    void ProcessContexts(EventManager &event_manager);

    /**
     * Get const iterator to context list.
     * @return const iterator
     */
    const std::vector<ContextView &>::const_iterator GetContextsViews();
};


#endif //_ContextManager_H_
