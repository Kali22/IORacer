#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <bits/stdc++.h>

class Window;
using WindowPtr = std::shared_ptr<Window>;

class Renderer;
using RendererPtr = std::shared_ptr<Renderer>;

using RenderWindowPtr = std::shared_ptr<sf::RenderWindow>;
