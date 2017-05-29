#pragma once

#include <SFML/Window/Event.hpp>

enum EventTypeE {
    SFML_EVENT,
    UI_EVENT
};

enum UIEventTypeE {
    UI_EVENT_CLICK,
    UI_EVENT_MOUSE_OVER,
    UI_EVENT_MOUSE_LOST,
};

class Event {
public:
    Event(UIEventTypeE type, const std::string &name);

    Event(const sf::Event &event);

    EventTypeE GetType() const;

    UIEventTypeE GetUIEventType() const;

    const std::string &GetUIElement() const;

    sf::Event GetSFMLEvent() const;

private:
    EventTypeE type_;

    // UI
    UIEventTypeE uiType_;
    std::string uiElement_;

    // SFML
    sf::Event sfmlEvent_;
};

