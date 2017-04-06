//
// Created by maciej on 30.03.17.
//

#include "Game.h"


Game::Game(sf::RenderWindow *window) : Module(window) {
    const sf::Vector2f game_button_size = sf::Vector2f(300, 80);
    std::shared_ptr<Button> return_button = std::make_shared<Button>(
            sf::Vector2f(400, 150),
            game_button_size,
            "Return",
            [&](sf::RenderWindow *window){
                close = true;
            }
    );

    objects.push_back(return_button);
    buttons.push_back(return_button);
}

int Game::run() {
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
