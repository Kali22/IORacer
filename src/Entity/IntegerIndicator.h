//
// Created by jacek on 20.04.17.
//

#pragma once

#include <Entity/Text.h>
#include <Entity/Updatable.h>

class IntegerIndicator : public Text, public Updatable {
public:
    IntegerIndicator(const int &param, sf::Vector2f position, std::string fontName,
                     float size, int minVal = 0, int maxVal = 99, bool leadingZeros = false, int fieldWidth = 2);

    IntegerIndicator(const int &param, sf::FloatRect frame, TextJustification position, std::string fontName,
                     float size, int minVal = 0, int maxVal = 99, bool leadingZeros = false, int fieldWidth = 2);

    void Draw(sf::RenderWindow *window) const;

    void Update();

protected:
    const int &data_;
    int minVal_;
    int maxVal_;
    int fieldWidth_;
    bool leadingZeros_;
};

using IntegerIndicatorPtr = std::shared_ptr<IntegerIndicator>;