#include "Text.h"

std::map<std::string, std::string> font{
        std::make_pair("impact", "/usr/share/fonts/truetype/msttcorefonts/impact.ttf")
};

Text::Text(std::string text, std::string fontName, sf::Vector2f position) {
    if (!sfFont_.loadFromFile(font[fontName])) {
        throw std::runtime_error("Font loading failed");
    }
    sfText_.setFont(sfFont_);
    sfText_.setCharacterSize(50);
    sfText_.setString(text);
    sfText_.setColor(sf::Color::White);
    // centering string
    auto bounds = sfText_.getGlobalBounds();
    int width = (int) bounds.width;
    int height = (int) bounds.height;
    sf::Vector2f center = position - sf::Vector2f(width, height) / 2.0f - sf::Vector2f(0, bounds.top);
    sfText_.setPosition(center);
}

void Text::draw(sf::RenderWindow *window) {
    window->draw(sfText_);
}

void Text::setText(std::string txt) {
    sfText_.setString(txt);
}