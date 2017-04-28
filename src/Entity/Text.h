#pragma once

#include <Entity/Movable.h>

/**
 * Text position within frame.
 */
enum TextJustification {
    TEXT_LEFT,
    TEXT_RIGHT,
    TEXT_CENTER
};

/**
 * Drawable piece of text.
 * @TODO Editable by streams...
 */
class Text : public Movable {
public:
    /**
     * Create floating text.
     */
    Text(std::string text, std::string fontName, sf::Vector2f position, float
    size);

    /**
     * Create text inside box.
     */
    Text(std::string text, std::string fontName, sf::FloatRect frame, float size, TextJustification position);

    void Draw(sf::RenderWindow *window) const;

    void SetText(std::string txt);

    void SetColor(sf::Color color);

    void SetFrameColor(sf::Color color);

    void SetFrameFillColor(sf::Color color);

    void SetFrameThickness(float thickness);

    void FrameOn();

    void FrameOff();

    void SetTextFrame(sf::FloatRect frame);

    sf::FloatRect GetSameFrameBelow(float margin);
    sf::FloatRect GetSameFrameAbove(float margin);
    sf::FloatRect GetSameFrameLeft(float margin);
    sf::FloatRect GetSameFrameRight(float margin);

    void SetPosition(const sf::Vector2f &pos);
    void SetPosition(float x, float y);
    void Move(const sf::Vector2f &dr);
    void Move(float dx, float dy);

protected:
    void CreateText(std::string text, std::string fontName, float size);

    void JustifyText();

    void SetDefaultFrameStyle();

    void SetDefaultMargin();

    bool frame_;
    sf::RectangleShape rectangleFrame_;
    TextJustification textPosition_;
    float sideMargin_;
    sf::Font sfFont_;
    sf::Text sfText_;
};

using TextPtr = std::shared_ptr<Text>;
