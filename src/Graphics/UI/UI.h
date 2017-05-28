#pragma once


#include <bits/stdc++.h>
#include <UI/UIElement.h>
#include <Event.h>
#include <UIBox.h>
#include <UITextBox.h>
#include <ViewportConst.h>
#include <UIMinimap.h>

/** @TODO Resize elements onload! */
class UI {
public:
    UI(ActivityPtr activity);

    UIBoxPtr CreateBox(std::string name, sf::FloatRect size  = centeredFullScreen);

    UIMinimapPtr CreateMinimap(std::string name, sf::FloatRect size, TexturePtr texture);

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

