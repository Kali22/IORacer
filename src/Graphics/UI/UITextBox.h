#pragma once


#include <SFML/Graphics/Text.hpp>
#include <UIElement.h>

class UITextBox : public UIElement {
public:
    UITextBox(int id, std::string name, std::string text, unsigned fontSize, sf::FloatRect size,
              ActivityPtr activity);

    void SetBackgroundColorHover(sf::Color color);

    void SetOutlineColorHover(sf::Color color);

    void SetBackgroundColor(sf::Color color);

    void SetOutlineColor(sf::Color color);

    void SetTextColor(sf::Color color);

    void SetTextColorHover(sf::Color color);

    void SetText(const std::string &text);

    void Render(RenderWindowPtr window);

private:
    sf::Font font_;
    sf::Text text_;
    sf::Color normalColor_;
    sf::Color normalOutlineColor_;
    sf::Color normalTextColor_;
    sf::Color hoverColor_;
    sf::Color hoverOutlineColor_;
    sf::Color hoverTextColor_;
    float verticalFix;

    void SetHoverColors();
};

using UITextBoxPtr = std::shared_ptr<UITextBox>;
