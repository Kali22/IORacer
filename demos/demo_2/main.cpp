#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Module/Menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    Menu menu(&window);
    menu.run();

    window.close();

    return 0;
}