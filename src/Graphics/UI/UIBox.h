#pragma once


#include <UIElement.h>

class UIBox : public UIElement {
public:
    UIBox(int id, std::string name, WeakActivityPtr activity);

    UIBox(int id, std::string name, sf::FloatRect size, WeakActivityPtr activity);
};

using UIBoxPtr = std::shared_ptr<UIBox>;
