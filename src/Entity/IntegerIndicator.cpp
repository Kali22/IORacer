//
// Created by jacek on 21.04.17.
//

#include <Entity/IntegerIndicator.h>

IntegerIndicator::IntegerIndicator(const int &param, sf::Vector2f position, std::string fontName,
                                   float size, int minVal, int maxVal, bool leadingZeros, int fieldWidth) :
        Text(std::string(""), fontName, position, size),
        data_(param),
        leadingZeros_(leadingZeros),
        fieldWidth_(fieldWidth),
        minVal_(minVal),
        maxVal_(maxVal) {
    Update();
}

IntegerIndicator::IntegerIndicator(const int &param, sf::FloatRect frame,
                                   TextJustification position, std::string fontName,
                                   float size, int minVal, int maxVal, bool leadingZeros, int fieldWidth) :
        Text(std::string(""), fontName, frame, size, position),
        data_(param),
        leadingZeros_(leadingZeros),
        fieldWidth_(fieldWidth),
        minVal_(minVal),
        maxVal_(maxVal) {
    Update();
}

void IntegerIndicator::Draw(sf::RenderWindow *window) const {
    Text::Draw(window);
}

void IntegerIndicator::Update() {
    std::stringstream ss;
    if (data_ < minVal_ || maxVal_ < data_) {
        ss << std::string(fieldWidth_, '-');
    } else {
        if (leadingZeros_) {
            ss << std::setfill('0');
            ss << std::setw(fieldWidth_);
        }
        ss << data_;
    }
    SetText(ss.str());
}
