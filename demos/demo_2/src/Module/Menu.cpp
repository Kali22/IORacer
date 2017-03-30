//
// Created by maciej on 30.03.17.
//

#include "Menu.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include <../Entity/Button.h>
#include "Game.h"
#include "Workshop.h"


Menu::Menu(sf::RenderWindow *window) : Module(window) {
    const sf::Vector2f menu_button_size = sf::Vector2f(300, 80);
    // set buttons
    std::shared_ptr<Button> play_button = std::make_shared<Button>(
            sf::Vector2f(400, 150),
            menu_button_size,
            "Play",
            [&](sf::RenderWindow *window){
                Game game(window);
                game.run();
            }
    );

    std::shared_ptr<Button> workshop_button = std::make_shared<Button>(
            sf::Vector2f(400, 300),
            menu_button_size,
            "Workshop",
            [&](sf::RenderWindow *window){
                Workshop workshop(window);
                workshop.run();
            }
    );

    std::shared_ptr<Button> quit_button = std::make_shared<Button>(
            sf::Vector2f(400, 450),
            menu_button_size,
            "Quit",
            [&](sf::RenderWindow *window){
                close = true;
            }
    );

    // every drawable object
    objects.push_back(play_button);
    objects.push_back(workshop_button);
    objects.push_back(quit_button);

    // buttons
    buttons.push_back(play_button);
    buttons.push_back(workshop_button);
    buttons.push_back(quit_button);
}


int Menu::run() {
    while (!close)
    {
        bool mouse_click = false; // info for buttons

        // EVENT handling
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: end while loop
            if (event.type == sf::Event::Closed) {
                close = true;
            }
            // handle mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button ==  sf::Mouse::Left) {
                mouse_click = true;
            }
        }

        /// BUTTON things
        std::shared_ptr<Button> active_button = nullptr;
        sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window));
        // select hovered button, change style
        for (auto& button : buttons) {
            if (button->toggle_hover(mouse_pos)) {
                active_button = button;
            }
        }
        if (active_button != nullptr && mouse_click) {
            active_button->onClick(window);
        }

        // DRAWING
        window->clear(sf::Color(60, 70, 80));
        for (auto& drawable_object : objects) {
            drawable_object->draw(window);
        }
        window->display();
    }

    return 0;
}