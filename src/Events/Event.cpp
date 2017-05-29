#include "Event.h"

Event::Event(UIEventTypeE type, const std::string &name)
        : type_(UI_EVENT), uiType_(type), uiElement_(name) {
}

Event::Event(const sf::Event &event) : type_(SFML_EVENT), sfmlEvent_(event) {}

EventTypeE Event::GetType() const {
    return type_;
}

UIEventTypeE Event::GetUIEventType() const {
    return uiType_;
}

const std::string &Event::GetUIElement() const {
    return uiElement_;
}

sf::Event Event::GetSFMLEvent() const {
    return sfmlEvent_;
}
