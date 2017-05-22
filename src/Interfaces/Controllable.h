#pragma once

#include <SFML/Window/Event.hpp>
#include <bits/stdc++.h>

class Controllable {
public:
    virtual void EventAction(sf::Event event) = 0;
};

using ControlablePtr = std::shared_ptr<Controllable>;
