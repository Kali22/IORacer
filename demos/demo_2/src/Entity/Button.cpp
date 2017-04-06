//
// Created by maciej on 30.03.17.
//

#include "Button.h"

bool Button::hovered(sf::Vector2f mousePosition) {
    return background.getGlobalBounds().contains(mousePosition);
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string txt, std::function<void()> action) :
        background(size),
        position(pos),
        text(txt, "impact", pos),
        action(action) {
    background.setPosition(pos - size / 2.0f);
    background.setFillColor(sf::Color(128, 128, 128)); // Grey
    background.setOutlineColor(sf::Color(50, 120, 70));
}

bool Button::toggleHover(sf::Vector2f mousePosition) {
    if (hovered(mousePosition)) {
        background.setFillColor(sf::Color(64, 64, 64)); // Dark Grey
        background.setOutlineThickness(2);
        return true;
    } else {
        background.setFillColor(sf::Color(128, 128, 128)); // Grey
        background.setOutlineThickness(0);
        return false;
    }
}

void Button::draw(sf::RenderWindow *window) {
    window->draw(background);
    text.draw(window);
}

void Button::onClick() {
    action();
}