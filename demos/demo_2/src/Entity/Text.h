//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_TEXT_H
#define DEMO_2_TEXT_H

#include "Drawable.h"

class Text : public Drawable {
    sf::Font sf_font;
    sf::Text sf_text;
public:
    Text(std::string text, std::string font_path, sf::Vector2f position);

    void draw(sf::RenderWindow *window);

    void setText(std::string txt);
};

typedef std::shared_ptr <Text> Text_ptr;

#endif //DEMO_2_TEXT_H
