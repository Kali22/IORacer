//
// Created by maciej on 30.03.17.
//

#include "Text.h"

std::map<std::string, std::string> font {
    std::make_pair("impact", "/usr/share/fonts/truetype/msttcorefonts/impact.ttf")
};

Text::Text(std::string text, std::string font_name, sf::Vector2f position) {
    if (!sf_font.loadFromFile(font[font_name])) {
        throw std::runtime_error("Font loading failed");
    }
    sf_text.setFont(sf_font);
    sf_text.setCharacterSize(20);
    sf_text.setString(text);
    sf_text.setColor(sf::Color::White);
    // centering string
    auto bounds = sf_text.getGlobalBounds();
    int width = (int) bounds.width;
    int height = (int) bounds.height;
    sf::Vector2f center = position - sf::Vector2f(width, height) / 2.0f - sf::Vector2f(0, bounds.top);
    sf_text.setPosition(center);
}

void Text::Draw(sf::RenderWindow *window) {
    window->draw(sf_text);
}

void Text::SetString(std::string text) {
    sf_text.setString(text);
}
