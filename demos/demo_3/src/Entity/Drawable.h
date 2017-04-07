#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class Drawable {
public:
    virtual void Draw(sf::RenderWindow *window) = 0;
};

