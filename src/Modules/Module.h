#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include <Drawable.h>
#include <Button.h>


class Module {
public:
    Module(RenderWindowPtr window) : close_(false), window_(window) {}

    virtual int Run()=0;

protected:
    bool close_;
    RenderWindowPtr window_;
    std::vector<DrawablePtr> objects_;
    std::vector<ButtonPtr> buttons_;

    void RegisterButton(ButtonPtr button) {
        objects_.push_back(button);
        buttons_.push_back(button);
    }
};

using ModulePtr = std::shared_ptr<Module>;
