/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include "ContextManager.h"
#include <Event.h>

ContextManager::ContextManager() {
}

ContextManager::~ContextManager() {

}

void ContextManager::PropagateEvents(EventManager &event_manager) {
    Event event;
    while (event_manager.PopEvent(event)) {
        for (int i = 0; i < context_list.size(); ++i) {
            context_list[i].PushEvent(event);
        }
    }
}
