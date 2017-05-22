#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <string>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using RenderWindowPtr = std::shared_ptr<sf::RenderWindow>;

class Drawable {
public:
    virtual void Draw(RenderWindowPtr window) const = 0;
};
using DrawablePtr = std::shared_ptr<Drawable>;

