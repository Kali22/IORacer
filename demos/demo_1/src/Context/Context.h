/**
 *  @defgroup context Context
 *  Process abstraction
 */

/**
 *  @file
 *  @ingroup context
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _Context_H_
#define _Context_H_

#include <ContextEvents.h>
#include <Event.h>
#include <EventManager.h>
#include <string>
#include <ContextScene.h>
#include <ContextCameraView.h>

/**
 *  Context
 */
class Context {
private:
    /// Context ID
    int context_id;
    /// Context name
    std::string context_name;
    /// Context event queue
    ContextEvents context_events;

    /**
     * Context scene
     * Abstraction layer for all drawable contents and context presentation.
     */
    ContextScene context_scene;
public:
    /**
     * Create context
     */
    Context(int id, std::string name);

    /**
     * Destroy context
     */
    ~Context();

    /**
     * Pass event to context queue.
     * @param event
     */
    void PushEvent(Event &event);

    /**
     * Context main function.
     * @param event_manager
     */
    void Process(EventManager &event_manager);

    /**
     * Get context name
     * @return context name
     */
    const std::string &GetContextName() const;

    /**
     * Get context ID.
     * @return id
     */
    int GetContextId();

    /**
     * Get number of cameras belonging to this context.
     * @return # of cameras
     */
    int GetCamerasCount();

    /**
     * Get i-th camera view.
     * @param i camera id
     * @return Camera view
     */
    const ContextCameraView &GetCameraView(int i);
};

#endif //_Context_H_
