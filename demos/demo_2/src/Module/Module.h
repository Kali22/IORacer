#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include <Drawable.h>
#include <Button.h>


class Module {
public:
    Module(sf::RenderWindow *window) : close_(false), window_(window) {}

    virtual int run()=0;

    void setWindow(sf::RenderWindow *newWindow) {
        window_ = newWindow;
    }

protected:
    bool close_;
    sf::RenderWindow *window_;
    std::vector<DrawablePtr> objects_;
    std::vector<ButtonPtr> buttons_;

    void registerButton(ButtonPtr button) {
        objects_.push_back(button);
        buttons_.push_back(button);
    }
};

using ModulePtr = std::shared_ptr<Module>;
