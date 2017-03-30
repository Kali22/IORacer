//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_BUTTON_H
#define DEMO_2_BUTTON_H

#include "Drawable.h"
#include "Text.h"

class Button : public Drawable {
    sf::RectangleShape background;
    sf::Vector2f position;
    Text text;
    std::function<void(sf::RenderWindow *window)> callback;
public:
    bool hovered(sf::Vector2f mouse_position);

    Button(sf::Vector2f pos, sf::Vector2f size, std::string txt, std::function<void(sf::RenderWindow *window)> click);

    bool toggle_hover(sf::Vector2f mouse_position);

    void onClick(sf::RenderWindow *window);

    void draw(sf::RenderWindow *window);
};


#endif //DEMO_2_BUTTON_H
