//
// Created by jacek on 20.04.17.
//

#include "TimeIndicator.h"

TimeIndicator::TimeIndicator(const float &param, sf::Vector2f position, std::string fontName, float size) :
        Text(std::string(""), fontName, position, size),
        data_(param) {
    Update();
}

TimeIndicator::TimeIndicator(const float &param, sf::FloatRect frame, TextJustification position,
                             std::string fontName, float size) :
        Text(std::string(""), fontName, frame, size, position),
        data_(param) {
    Update();
}

void TimeIndicator::Draw(sf::RenderWindow *window) const {
    Text::Draw(window);
}

std::string TimeIndicator::GetTimeString(float time) const {
    std::stringstream ss;
    if (time < (99 * 60.f)) {
        ss << std::setfill('0') << std::setw(2);
        ss << (int) (time / 60.);
        ss << ":";
        ss << std::setfill('0') << std::setw(2);
        ss << (int) time % 60;
        ss << ".";
        ss << std::setfill('0') << std::setw(3);
        ss << (int) (time * 1000.0f) % 1000;
    } else {
        ss << "--:--.---";
    }
    return ss.str();
}

void TimeIndicator::Update() {
    SetText(GetTimeString(data_));
}
