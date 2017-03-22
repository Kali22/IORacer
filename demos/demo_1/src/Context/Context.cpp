/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include "Context.h"

Context::Context() {

}

Context::~Context() {

}

ContextView *Context::GetView() {
    return &view;
}

void Context::PushEvent(Event &event) {
    events.PushEvent(event);
}

void Context::Process(EventManager &event_manager) {
    Event event;
    while (events.PopEvent(event)) {
//         ... do sth with events and event manager
        switch (event.event_type) {
//            case EVENT_STH:
//              logic.make_action();
//            break;
            default:
                break;
        }
    }
}
