#pragma once

#include <Drawable.h>

class Text : public Drawable {
public:
    Text(std::string text, std::string font_path, sf::Vector2f position);
    void Draw(sf::RenderWindow *window) const;
    void SetString(std::string text);
private:
    sf::Font sf_font;
    sf::Text sf_text;
};
