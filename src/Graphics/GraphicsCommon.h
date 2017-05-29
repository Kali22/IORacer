#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Window;

class Renderer;

using WindowPtr = std::shared_ptr<Window>;
using RendererPtr = std::shared_ptr<Renderer>;
using RenderWindowPtr = std::shared_ptr<sf::RenderWindow>;
