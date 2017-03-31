/**
 *  @file
 *  @ingroup context_manager
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include <ContextManager.h>

ContextManager::ContextManager() {
    /// @TODO implementation?
}

ContextManager::~ContextManager() {
    /// @TODO implementation?
}

void ContextManager::ProcessEvents(EventServer &event_manager) {
    Event event;
//    while (event_manager.PopEvent(event)) {
//        for (int i = 0; i < context_list.size(); ++i) {
//            context_list[i].PushEvent(event);
//        }
//    }
}

void ContextManager::ProcessContexts(EventServer &event_manager) {
    for (int i = 0; i < context_list.size(); ++i) {
        context_list[i].Process(event_manager);
    }
}

void ContextManager::RenderContexts(RendererHandler &renderer_handler) {
    for (int i = 0; i < context_list.size(); ++i) {
        int cameras_n = context_list[i].GetCamerasCount();
        for (int j = 0; j < cameras_n; ++j) {
            renderer_handler.Render(context_list[i].GetCameraView(j));
        }
    }
}