//
// Created by pawel on 30.03.17.
//

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Car.h>

#include "Race.h"

//#ifndef DEGTORAD
//#define DEGTORAD 0.0174532925199432957f
//#define RADTODEG 57.295779513082320876f
//#endif

void setclr(int *reg, int mask, int type) {
    if (type)
        *reg |= mask;
    else
        *reg &= ~mask;
}

void HandleKeyboard(sf::Event::KeyEvent Event, int *state, int type) {
    /// @TODO change to map
    switch (Event.code) {
        case sf::Keyboard::Key::Left:
            setclr(state, LEFT, type);
            break;
        case sf::Keyboard::Key::Up:
            setclr(state, UP, type);
            break;
        case sf::Keyboard::Key::Down:
            setclr(state, DOWN, type);
            break;
        case sf::Keyboard::Key::Right:
            setclr(state, RIGHT, type);
            break;
        default:
            break;
    }
}


void Race::Run() {
    /** Prepare the world */
    b2Vec2 Gravity(0.f, 0.f);
    b2World World(Gravity);

    sf::Texture BoxTexture;
    BoxTexture.loadFromFile("../resource/car.png");
    int carState = 0;
    Car car(&World, 300, 300);
    car.setCharacteristics(180, -80, 150);

    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            // Close window : exit
            if (Event.type == sf::Event::Closed) {
                window.close();
            } else if (Event.type == sf::Event::KeyPressed) {
                HandleKeyboard(Event.key, &carState, 1);
            } else if (Event.type == sf::Event::KeyReleased) {
                HandleKeyboard(Event.key, &carState, 0);
            }
        }

        /** Simulate the world */
        car.Update(carState);
        World.Step(1 / 60.f, 8, 3);

        window.clear(sf::Color::White);
        car.Draw(window, BoxTexture);
        window.display();
    }
}
