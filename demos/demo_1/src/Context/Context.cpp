/**
 *  @file
 *  @ingroup context
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include <Context.h>

Context::Context(int id, std::string name) {
    context_name = name;
    context_id  = id;
}

Context::~Context() {

}

void Context::PushEvent(Event &event) {
    context_events.PushEvent(event);
}

void Context::Process(EventServer &event_manager) {
    //====================== CONTEXT EVENTS PROCESSING
    Event event;
    while (context_events.PopEvent(event)) {
        switch (event.event_type) {
            default:
                break;
        }
    }

    //====================== CONTEXT MAIN ROUTINES
    // ...
    // ...
    // ...
}

const std::string &Context::GetContextName() const {
    return context_name;
}

int Context::GetContextId() {
    return context_id;
}

int Context::GetCamerasCount() {
    return context_scene.GetCamerasCount();
}

const ContextCameraView &Context::GetCameraView(int i) {
    return context_scene.GetCameraView(i);
}

