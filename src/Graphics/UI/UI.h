#pragma once


#include <bits/stdc++.h>
#include <UI/UIElement.h>
#include "../../Events/Event.h"
#include "UIBox.h"
#include "UITextBox.h"

/** @TODO Resize elements onload! */
class UI {
public:
    UI(ActivityPtr activity);

    UIBoxPtr CreateBox(std::string name, sf::FloatRect size  = sf::FloatRect(0.5, 0.5, 1, 1));

    UITextBoxPtr CreateTextBox(std::string name, std::string text, int fontSize, sf::FloatRect size);

    UIElementPtr GetElementByIdx(int i);

    UIElementPtr GetElementByName(std::string name);

    int GetElementsCount() const;

    void EventAction(sf::Event event);

private:
    std::vector<UIElementPtr> list_;

    ActivityPtr activity_;
};

using UIPtr = std::shared_ptr<UI>;

