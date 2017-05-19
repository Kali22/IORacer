#pragma once

#include <SFML/Window/Event.hpp>
#include "UIEvent.h"

enum EventTypeE {
    SFML_EVENT,
    UI_EVENT
};

class Event {
public:
    Event(UIEvent event);
    Event(sf::Event event);

    EventTypeE type;
    union {
        UIEvent uiEvent;
        sf::Event sfmlEvent;
    };
};

