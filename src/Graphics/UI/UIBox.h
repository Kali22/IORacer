#pragma once


#include <UIElement.h>

class UIBox : public UIElement {
public:
    UIBox(int id, std::string name, ActivityPtr activity);

    UIBox(int id, std::string name, sf::FloatRect size, ActivityPtr activity);
};

using UIBoxPtr = std::shared_ptr<UIBox>;
