#pragma once

#include <string>
#include <UI/UIElement.h>

enum UIEventType {
    UI_EVENT_CLICK,
    UI_EVENT_MOUSE_OVER,
    UI_EVENT_MOUSE_LOST,
};

class UIEvent {
public:
    UIEvent();

    UIEvent(UIEventType type, int id);

    int type;
    int id;
};

