#pragma once


#include <bits/stdc++.h>
#include <UIElement.h>
#include <UIBox.h>
#include <UITextBox.h>
#include <UIMinimap.h>
#include <Event.h>
#include <ViewportConst.h>
#include <ActivityCommon.h>

/** @TODO Resize elements on load! */
class UI {
public:
    UI(WeakActivityPtr activity);

    UIBoxPtr CreateBox(std::string name, sf::FloatRect size = centeredFullScreen);

    UIMinimapPtr CreateMinimap(std::string name, sf::FloatRect size,
                               RealVec mapSize, TexturePtr texture);

    UITextBoxPtr CreateTextBox(std::string name, std::string text, int fontSize, sf::FloatRect size);

    UIElementPtr GetElementByName(const std::string &name);

    unsigned GetElementsCount() const;

    void EventAction(sf::Event event);

    void DeleteElementByName(const std::string &name);

    std::map<std::string, UIElementPtr>::iterator GetElements();

private:
    std::map<std::string, UIElementPtr> list_;

    WeakActivityPtr activity_;
};

using UIPtr = std::shared_ptr<UI>;
