#include <SFML/Window/Event.hpp>
#include <Window.h>
#include <Renderer.h>

Window::Window(std::string appName) : appName_(appName),
                                      modes_(sf::VideoMode::getFullscreenModes()),
                                      desktop_(sf::VideoMode::getDesktopMode()) {
    window_ = std::make_shared<sf::RenderWindow>(desktop_, appName, sf::Style::None);
    window_->setFramerateLimit(60);
    renderer_ = std::make_shared<Renderer>(window_);
}

bool Window::PollEvent(sf::Event &event) {
    return window_->pollEvent(event);
}

RenderWindowPtr Window::GetRenderWindow() const {
    return window_;
}

RendererPtr Window::GetRenderer() const {
    return renderer_;
}
