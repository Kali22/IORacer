#include "Event.h"

Event::Event(UIEventType type, const std::string &name) : type(UI_EVENT), uiType(type), uiElenemt(name) {

}

Event::Event(const sf::Event &event) : type(SFML_EVENT), sfmlEvent(event) {

}
