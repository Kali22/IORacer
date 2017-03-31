/**
 *  @defgroup context_manager Context Manager
 *  Context manager object.
 */

/**
 *  @file
 *  @ingroup context_manager
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _ContextManager_H_
#define _ContextManager_H_

#include <Context.h>
#include <EventServer.h>
#include <RendererHandler.h>
#include <vector>

/**
 * Context manager.
 * Contexts' container, event and renderer propagator.
 */
class ContextManager {
private:
    /// Collection of all contexts
    std::vector<Context> context_list;
public:
    /**
     * Create.
     */
    ContextManager();

    /**
     * Destroy.
     */
    ~ContextManager();

    /**
     * Propagate collected events to contexts.
     * @param event_manager
     */
    void ProcessEvents(EventServer &event_manager);

    /**
     * Run each event and let them do a job.
     * @param event_manager
     */
    void ProcessContexts(EventServer &event_manager);

    /**
     * Render appropriate contexts on screen.
     * @param renderer_handler
     */
    void RenderContexts(RendererHandler &renderer_handler);
};

#endif //_ContextManager_H_
