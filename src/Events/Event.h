#pragma once

#include <SFML/Window/Event.hpp>

enum EventTypeE {
    SFML_EVENT,
    UI_EVENT
};

enum UIEventType {
    UI_EVENT_CLICK,
    UI_EVENT_MOUSE_OVER,
    UI_EVENT_MOUSE_LOST,
};

class Event {
public:
    Event(UIEventType type, const std::string &name);
    Event(const sf::Event &event);

    EventTypeE type;

    // UI
    UIEventType uiType;
    std::string uiElenemt;
    // SFML
    sf::Event sfmlEvent;
};

