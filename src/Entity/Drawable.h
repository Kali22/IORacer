#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class Drawable {
public:
    virtual void Draw(sf::RenderWindow *window) const = 0;
};

using DrawablePtr = std::shared_ptr<Drawable>;
