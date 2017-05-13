#pragma once


#include <Controllable.h>
#include <Object.h>

class Vehicle : public Controllable {
public:
    Vehicle(ObjectPtr vehicleObject);
    virtual void EventAction(sf::Event event);

private:
    ObjectPtr vehicleObject_;

    void HandleMouse(sf::Event::MouseMoveEvent mouse);
    void HandleKeyboard(sf::Event::KeyEvent keys);
};

using VehiclePtr = std::shared_ptr<Vehicle>;
