//
// Created by maciej on 30.03.17.
//

#include "Button.h"

bool Button::hovered(sf::Vector2f mousePosition) {
    return background_.getGlobalBounds().contains(mousePosition);
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string txt, std::function<void()> action) :
        background_(size),
        position_(pos),
        text_(txt, "impact", pos),
        action_(action) {
    background_.setPosition(pos - size / 2.0f);
    background_.setFillColor(sf::Color(128, 128, 128)); // Grey
    background_.setOutlineColor(sf::Color(50, 120, 70));
}

bool Button::toggleHover(sf::Vector2f mousePosition) {
    if (hovered(mousePosition)) {
        background_.setFillColor(sf::Color(64, 64, 64)); // Dark Grey
        background_.setOutlineThickness(2);
        return true;
    } else {
        background_.setFillColor(sf::Color(128, 128, 128)); // Grey
        background_.setOutlineThickness(0);
        return false;
    }
}

void Button::draw(sf::RenderWindow *window) {
    window->draw(background_);
    text_.draw(window);
}

void Button::onClick() {
    action_();
}