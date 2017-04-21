#include "Text.h"
#include <string>
std::map<std::string, std::string> font{
        std::make_pair("impact", "../resource/fonts/impact.ttf"),
        std::make_pair("andale_mono", "../resource/fonts/Andale_Mono.ttf"),
        std::make_pair("calibri", "../resource/fonts/calibri.ttf"),
        std::make_pair("calibrib", "../resource/fonts/calibrib.ttf"),
        std::make_pair("consola", "../resource/fonts/consola.ttf")
};

Text::Text(std::string text, std::string fontName, sf::Vector2f position,
           float size) {
    CreateText(text, fontName, size);
    frame_ = false;
    SetTextFrame(sf::FloatRect(position.x, position.y, 0.f, 0.f));
    SetDefaultFrameStyle();
    textPosition_ = TEXT_CENTER;
    SetDefaultMargin();
    JustifyText();
}

Text::Text(std::string text, std::string fontName, sf::FloatRect frame, float size, TextJustification position) {
    CreateText(text, fontName, size);
    frame_ = false;
    SetTextFrame(frame);
    SetDefaultFrameStyle();
    textPosition_ = position;
    SetDefaultMargin();
    JustifyText();
}

void Text::Draw(sf::RenderWindow *window) const {
    if (frame_)
        window->draw(rectangleFrame_);
    window->draw(sfText_);
}

void Text::SetText(std::string txt) {
    sfText_.setString(txt);
    JustifyText();
}

void Text::SetColor(sf::Color color) {
    sfText_.setColor(color);
}

void Text::CreateText(std::string text, std::string fontName, float size) {
    if (!sfFont_.loadFromFile(font[fontName])) {
        throw std::runtime_error("Font loading failed");
    }
    sfText_.setFont(sfFont_);
    sfText_.setCharacterSize(size);
    sfText_.setString(text);
    sfText_.setColor(sf::Color::White);
}

void Text::JustifyText() {
    auto position = rectangleFrame_.getPosition();
    auto size = rectangleFrame_.getSize();
    auto bounds = sfText_.getGlobalBounds();
    float width = bounds.width;
    float height = bounds.height;
    float textPositionY = position.y + size.y / 2.f - height / 2.0f * 1.5f;
    float textPositionX = position.x;
    if (textPosition_ == TEXT_CENTER) {
        textPositionX += size.x / 2.f - width / 2.0f;
    } else if (textPosition_ == TEXT_RIGHT){
        textPositionX += size.x - width - sideMargin_;
    } else {
        textPositionX += sideMargin_;
    }
    sfText_.setPosition(textPositionX, textPositionY);
}

void Text::FrameOn() {
    frame_ = true;
}

void Text::FrameOff() {
    frame_ = false;
}

void Text::SetTextFrame(sf::FloatRect frame) {
    rectangleFrame_.setOrigin(0, 0);
    rectangleFrame_.setSize(sf::Vector2f(frame.width, frame.height));
    rectangleFrame_.setPosition(frame.left, frame.top);
    JustifyText();
}

void Text::SetDefaultFrameStyle() {
    rectangleFrame_.setFillColor(sf::Color(30, 30, 30, 50));
    rectangleFrame_.setOutlineColor(sf::Color(200, 200, 200, 80));
    rectangleFrame_.setOutlineThickness(0.f);
}

void Text::SetDefaultMargin() {
    sideMargin_ = 5.f;
}

void Text::SetFrameColor(sf::Color color) {
    rectangleFrame_.setOutlineColor(color);
}

void Text::SetFrameFillColor(sf::Color color) {
    rectangleFrame_.setFillColor(color);
}

void Text::SetFrameThickness(float thickness) {
    rectangleFrame_.setOutlineThickness(thickness);
}

sf::FloatRect Text::GetSameFrameBelow(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.top += rect.height + margin;
    return rect;
}

sf::FloatRect Text::GetSameFrameAbove(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.top -= rect.height + margin;
    return rect;
}

sf::FloatRect Text::GetSameFrameLeft(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.left -= rect.width + margin;
    return rect;
}

sf::FloatRect Text::GetSameFrameRight(float margin) {
    sf::FloatRect rect = rectangleFrame_.getGlobalBounds();
    rect.left += rect.width + margin;
    return rect;
}

void Text::SetPosition(const sf::Vector2f &pos) {
    rectangleFrame_.setPosition(pos);
    JustifyText();
}

void Text::SetPosition(float x, float y) {
    rectangleFrame_.setPosition(x, y);
    JustifyText();
}

void Text::Move(const sf::Vector2f &dr) {
    rectangleFrame_.move(dr);
    JustifyText();
}

void Text::Move(float dx, float dy) {
    rectangleFrame_.move(dx, dy);
    JustifyText();
}

