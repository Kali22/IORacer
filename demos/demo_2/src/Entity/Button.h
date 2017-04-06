//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_BUTTON_H
#define DEMO_2_BUTTON_H

#include "Drawable.h"
#include "Text.h"

class Button : public Drawable {

protected:
    sf::RectangleShape background;
    sf::Vector2f position;
    Text text;
    std::function<void()> action;

public:
    bool hovered(sf::Vector2f mouse_position);

    Button(sf::Vector2f pos, sf::Vector2f size, std::string txt, std::function<void()> action);

    bool toggleHover(sf::Vector2f mouse_position);

    void onClick();

    void draw(sf::RenderWindow *window);
};

using Button_ptr = std::shared_ptr<Button>;

#endif //DEMO_2_BUTTON_H
