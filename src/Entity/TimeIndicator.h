//
// Created by jacek on 20.04.17.
//

#pragma once

#include <Entity/Text.h>
#include <Entity/Updatable.h>

class TimeIndicator : public Text, public Updatable {
public:
    TimeIndicator(const float &param, sf::Vector2f position, std::string fontName, float size);

    TimeIndicator(const float &param, sf::FloatRect frame, TextJustification position,
                  std::string fontName, float size);

    void Draw(sf::RenderWindow *window) const;

    void Update();

protected:
    std::string GetTimeString(float time) const;

    const float &data_;
};

using TimeIndicatorPtr = std::shared_ptr<TimeIndicator>;