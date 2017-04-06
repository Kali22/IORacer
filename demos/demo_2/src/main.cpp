#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <Model/GameData.h>

#include <Menu.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    GameData_ptr gameData = std::make_shared<GameData>();
    Menu_ptr menu = std::make_shared<Menu>(&window, gameData);
    menu->run();

    window.close();

    return 0;
}