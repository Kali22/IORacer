#include "Game.h"

Game::Game(sf::RenderWindow *window, GameDataPtr gameData) : Module(window), gameData_(gameData) {
    const sf::Vector2f gameButtonSize = sf::Vector2f(300, 80);
    auto returnButton = std::make_shared<Button>(
            sf::Vector2f(400, 150),
            gameButtonSize,
            "Return",
            [this]() {
                close_ = true;
            }
    );

    objects_.push_back(returnButton);
    buttons_.push_back(returnButton);
}

int Game::run() {
    close_ = false;
    while (!close_) {
        bool mouseClick = false; // info for buttons

        // EVENT handling
        sf::Event event;
        while (window_->pollEvent(event)) {
            // "close_ requested" event: end while loop
            if (event.type == sf::Event::Closed) {
                close_ = true;
            }
            // handle mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mouseClick = true;
            }
        }

        /// BUTTON things
        ButtonPtr activeButton = nullptr;
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window_));
        // select hovered button, change style
        for (auto &button : buttons_) {
            if (button->toggleHover(mousePos)) {
                activeButton = button;
            }
        }
        if (activeButton != nullptr && mouseClick) {
            activeButton->onClick();
        }

        // DRAWING
        window_->clear(sf::Color(60, 70, 80));
        for (auto &drawableObject : objects_) {
            drawableObject->draw(window_);
        }
        window_->display();
    }

    return 0;
}