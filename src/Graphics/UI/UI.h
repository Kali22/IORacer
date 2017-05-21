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

    UIElementPtr GetElementByName(const std::string &name);

    int GetElementsCount() const;

    void EventAction(sf::Event event);

    void DeleteElementByName(const std::string &name);

    std::map<std::string, UIElementPtr>::iterator GetElements();
private:
    std::map<std::string, UIElementPtr> list_;

    ActivityPtr activity_;
};

using UIPtr = std::shared_ptr<UI>;

