#include "Vehicle.h"

void Vehicle::EventAction(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            HandleKeyboard(event.key);
            break;
        case sf::Event::MouseMoved:
            HandleMouse(event.mouseMove);
            break;
    }
}

Vehicle::Vehicle(ObjectPtr vehicleObject) : vehicleObject_(vehicleObject){

}

void Vehicle::HandleMouse(sf::Event::MouseMoveEvent mouse) {
    /// @TODO Dodane tymczasowo z hardcorodwanymi rozmiarami mapy...
    vehicleObject_->SetPosition((mouse.x / 1920.) * 500 - 250, (mouse.y / 1080.) * 200. - 100);
}

void Vehicle::HandleKeyboard(sf::Event::KeyEvent keys) {
    if (keys.code == sf::Keyboard::Up) {
        vehicleObject_->Move(0, 2);
    }
    if (keys.code == sf::Keyboard::Down) {
        vehicleObject_->Move(sf::Vector2f(0,-2));
    }
    if (keys.code == sf::Keyboard::Left) {
        if (keys.shift)
            vehicleObject_->Rotate(-10);
        else
            vehicleObject_->Move(-2, 0);
    }
    if (keys.code == sf::Keyboard::Right) {
        if (keys.shift)
            vehicleObject_->Rotate(10);
        else
            vehicleObject_->Move(2, 0);
    }
}
