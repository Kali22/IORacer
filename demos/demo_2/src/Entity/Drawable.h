//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_DRAWABLE_H
#define DEMO_2_DRAWABLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class Drawable {
public:
    virtual void draw(sf::RenderWindow *window)=0;
};

using Drawable_ptr = std::shared_ptr<Drawable>;

#endif //DEMO_2_DRAWABLE_H
