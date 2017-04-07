#pragma once

#include "Drawable.h"

class Text : public Drawable {
public:
    Text(std::string text, std::string fontPath, sf::Vector2f position);

    void draw(sf::RenderWindow *window);

    void setText(std::string txt);

private:
    sf::Font sfFont_;
    sf::Text sfText_;
};

using TextPtr = std::shared_ptr<Text>;