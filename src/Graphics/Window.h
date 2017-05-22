#pragma once

#include <string>
#include <SFML/Window/VideoMode.hpp>
#include <GraphicsCommon.h>

class Window {
public:
    Window(std::string appName);

    bool PollEvent(sf::Event &event);

    RenderWindowPtr GetRenderWindow() const;

    RendererPtr GetRenderer() const;
private:
    std::string appName_;
    std::vector<sf::VideoMode> modes_;
    sf::VideoMode desktop_;

    RenderWindowPtr window_;
    RendererPtr renderer_;
};
