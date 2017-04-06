//
// Created by maciej on 30.03.17.
//

#include "Workshop.h"

/*
void Workshop::addButton(const sf::Vector2f &position,
                         const sf::Vector2f &button_size, std::string text,
                         std::function<void(sf::RenderWindow *window)> func) {
    registerButton(std::make_shared<RedirectButton>(position, button_size, text, func));
}*/

Workshop::Workshop(sf::RenderWindow *window, GameData_ptr gamedata) : Module(window), gameData(gamedata) {

    const sf::Vector2f gameButtonSize = sf::Vector2f(400, 80);
    const sf::Vector2f statsButtonSize = sf::Vector2f(50, 50);
    const sf::Vector2f textFieldSize = sf::Vector2f(200, 60);

    returnButton = std::make_shared<Button>(
            sf::Vector2f(400, 520),
            gameButtonSize,
            "Return to menu",
            [this]() {
                close = true;
            });
    registerButton(returnButton);


    std::string plus = "+";
    std::string minus = "-";
    maxSpeedText = std::make_shared<Text>(
            std::to_string((int) gameData->car->maxSpeed), "impact", sf::Vector2f(400, 100));
    objects.push_back(maxSpeedText);

    minusMaxSpeed = std::make_shared<Button>(
            sf::Vector2f(250, 100),
            statsButtonSize,
            minus,
            [this]() {
                gameData->car->maxSpeed--;
                maxSpeedText->setText(std::to_string((int) gameData->car->maxSpeed));
            });
    registerButton(minusMaxSpeed);

    plusMaxSpeed = std::make_shared<Button>(
            sf::Vector2f(550, 100),
            statsButtonSize,
            plus,
            [this]() {
                gameData->car->maxSpeed++;
                maxSpeedText->setText(std::to_string((int) gameData->car->maxSpeed));
            });
    registerButton(plusMaxSpeed);

    accelerationText = std::make_shared<Text>(
            std::to_string((int) gameData->car->acceleration), "impact", sf::Vector2f(400, 200));
    objects.push_back(accelerationText);

    minusMaxSpeed = std::make_shared<Button>(
            sf::Vector2f(250, 200),
            statsButtonSize,
            minus,
            [this]() {
                gameData->car->acceleration--;
                accelerationText->setText(std::to_string((int) gameData->car->acceleration));
            });
    registerButton(minusMaxSpeed);

    plusMaxSpeed = std::make_shared<Button>(
            sf::Vector2f(550, 200),
            statsButtonSize,
            plus,
            [this]() {
                gameData->car->acceleration++;
                accelerationText->setText(std::to_string((int) gameData->car->acceleration));
            });
    registerButton(plusMaxSpeed);
}

int Workshop::run() {
    close = false;
    while (!close) {
        bool mouseClick = false; // info for buttons

        // EVENT handling
        sf::Event event;
        while (window->pollEvent(event)) {
            // "close requested" event: end while loop
            if (event.type == sf::Event::Closed) {
                close = true;
            }
            // handle mouse click
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                mouseClick = true;
            }
        }

        /// BUTTON things
        std::shared_ptr <Button> activeButton = nullptr;
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
        // select hovered button, change style
        for (auto &button : buttons) {
            if (button->toggleHover(mousePos)) {
                activeButton = button;
            }
        }
        if (activeButton != nullptr && mouseClick) {
            activeButton->onClick();
        }

        // DRAWING
        window->clear(sf::Color(60, 70, 80));
        for (auto &drawableObject : objects) {
            drawableObject->draw(window);
        }
        window->display();
    }
    return 0;
}
