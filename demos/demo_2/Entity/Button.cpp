//
// Created by maciej on 30.03.17.
//

#include "Button.h"

bool Button::hovered(sf::Vector2f mouse_position) {
    return background.getGlobalBounds().contains(mouse_position);
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string txt, std::function<void(sf::RenderWindow *window)> click) :
        background(size),
        position(pos),
        text(txt, "impact", pos),
        callback(click) {
    background.setPosition(pos - size / 2.0f);
    background.setFillColor(sf::Color(128, 128, 128)); // Grey
    background.setOutlineColor(sf::Color(50, 120, 70));
}

bool Button::toggle_hover(sf::Vector2f mouse_position) {
    if (hovered(mouse_position)) {
        background.setFillColor(sf::Color(64, 64, 64)); // Dark Grey
        background.setOutlineThickness(2);
        return true;
    }
    else {
        background.setFillColor(sf::Color(128, 128, 128)); // Grey
        background.setOutlineThickness(0);
        return false;
    }
}

void Button::onClick(sf::RenderWindow *window) {
    callback(window);
}

void Button::draw(sf::RenderWindow *window) {
    window->draw(background);
    text.draw(window);
}