#include "Event.h"

Event::Event(UIEvent event) : type(UI_EVENT), uiEvent(event) {

}

Event::Event(sf::Event event) : type(SFML_EVENT), sfmlEvent(event){

}
