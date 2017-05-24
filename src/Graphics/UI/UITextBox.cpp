#include <Fonts.h>
#include "UITextBox.h"

UITextBox::UITextBox(int id, std::string name, std::string text, int fontSize, sf::FloatRect size,
                     ActivityPtr activity)
        : UIElement(id, name, size,
                    activity) {
    if (!font_.loadFromFile(fonts["impact"])) {
        throw std::runtime_error("Font loading failed");
    }
    text_ = sf::Text(text, font_);
    text_.setCharacterSize(fontSize);
    normalColor_ = sf::Color::Transparent;
    hoverColor_ = sf::Color::Transparent;
    hoverOutlineColor_= sf::Color::Transparent;
    normalOutlineColor_ = sf::Color::Transparent;
    verticalFix = text_.getGlobalBounds().top;
}

void UITextBox::SetBackgroundColorHover(sf::Color color) {
    hoverColor_ = color;
}

void UITextBox::SetOutlineColorHover(sf::Color color) {
    hoverOutlineColor_ = color;
}

void UITextBox::SetTextColor(sf::Color color) {
    normalTextColor_ = color;
}

void UITextBox::SetTextColorHover(sf::Color color) {
    hoverTextColor_ = color;
}

void UITextBox::Render(RenderWindowPtr window) {
    if (hover_) {
        bounds_.setFillColor(hoverColor_);
        bounds_.setOutlineColor(hoverOutlineColor_);
        text_.setFillColor(hoverTextColor_);
    } else {
        bounds_.setFillColor(normalColor_);
        bounds_.setOutlineColor(normalOutlineColor_);
        text_.setFillColor(normalTextColor_);
    }
    auto size = bounds_.getGlobalBounds();
    auto textSize = text_.getGlobalBounds();
    text_.setPosition(size.left + size.width * 0.5, size.top + size.height * 0.5);
    text_.setOrigin(textSize.width * 0.5, textSize.height * 0.5 + verticalFix);
    window->draw(bounds_);
    window->draw(text_);
}

void UITextBox::SetBackgroundColor(sf::Color color) {
    normalColor_ = color;
}

void UITextBox::SetOutlineColor(sf::Color color) {
    normalOutlineColor_ = color;
}

void UITextBox::SetText(const std::string &text) {
    text_.setString(text);
}
