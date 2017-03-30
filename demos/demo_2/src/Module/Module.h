//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_MODULE_H
#define DEMO_2_MODULE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include "../Entity/Drawable.h"
#include "../Entity/Button.h"

class Module {
protected:
    bool close;
    sf::RenderWindow *window;
    std::vector<std::shared_ptr<Drawable> > objects;
    std::vector<std::shared_ptr<Button> > buttons;
public:
    Module(sf::RenderWindow *window) : close(false), window(window), objects(), buttons() {}
    virtual int run() { return 0; }
};


#endif //DEMO_2_MODULE_H
