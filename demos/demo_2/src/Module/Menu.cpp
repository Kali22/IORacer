//
// Created by maciej on 30.03.17.
//

#include "Menu.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include <GameData.h>


Menu::Menu(sf::RenderWindow *window, GameData_ptr gameplay) :
        Module(window), gameData(gameplay), workshop(std::make_shared<Workshop>(window, gameData)),
        game(std::make_shared<Game>(window, gameData)) {

    sf::Vector2f menuButtonSize = sf::Vector2f(300, 80);
    // set buttons
    playButton = std::make_shared<Button>(
            sf::Vector2f(400, 150),
            menuButtonSize,
            "Play",
            [this]() {
                game->run();
            }
    );

    workshopButton = std::make_shared<Button>(
            sf::Vector2f(400, 300),
            menuButtonSize,
            "Workshop",
            [this]() {
                workshop->run();
            }
    );

    quitButton = std::make_shared<Button>(
            sf::Vector2f(400, 450),
            menuButtonSize,
            "Quit",
            [this]() {
                close = true;
            }
    );

    // every drawable object
    objects.push_back(playButton);
    objects.push_back(workshopButton);
    objects.push_back(quitButton);

    // buttons
    buttons.push_back(playButton);
    buttons.push_back(workshopButton);
    buttons.push_back(quitButton);
}


int Menu::run() {
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
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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