//
// Created by maciej on 30.03.17.
//

#ifndef DEMO_2_MODULE_H
#define DEMO_2_MODULE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include <Drawable.h>
#include <Button.h>


class Module {
protected:
    bool close;
    sf::RenderWindow *window;
    std::vector <Drawable_ptr> objects;
    std::vector <Button_ptr> buttons;

    void registerButton(Button_ptr button) {
        objects.push_back(button);
        buttons.push_back(button);
    }

public:
    Module(sf::RenderWindow *window) : close(false), window(window) {}

    virtual int run()=0;

    void setWindow(sf::RenderWindow *newWindow) {
        window = newWindow;
    }

};

using Module_ptr = std::shared_ptr<Module>;


#endif //DEMO_2_MODULE_H
