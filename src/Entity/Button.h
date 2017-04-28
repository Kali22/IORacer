#pragma once

#include "Drawable.h"
#include "Text.h"

class Button : public Drawable {
public:
    bool Hovered(sf::Vector2f mousePosition);

    Button(sf::Vector2f pos, sf::Vector2f size, std::string txt, std::function<void()> action);

    bool ToggleHover(sf::Vector2f mousePosition);

    void OnClick();

    void Draw(sf::RenderWindow *window) const;

protected:
    sf::RectangleShape background_;
    sf::Vector2f position_;
    Text text_;
    std::function<void()> action_;
};

using ButtonPtr = std::shared_ptr<Button>;
