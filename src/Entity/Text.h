#pragma once

#include "Drawable.h"

class Text : public Drawable {
public:
    Text(std::string text, std::string fontPath, sf::Vector2f position, float
    size);

    void Draw(sf::RenderWindow *window) const;

    void SetText(std::string txt);

    void SetColor(sf::Color color);

private:
    sf::Font sfFont_;
    sf::Text sfText_;
};

using TextPtr = std::shared_ptr<Text>;