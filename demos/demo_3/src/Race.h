//
// Created by pawel on 30.03.17.
//

#ifndef RACE_H

#include <SFML/Graphics.hpp>

class Race {
private:
    sf::RenderWindow& window;

public:
    Race(sf::RenderWindow& win) : window(win) { }
    void Run();
};

#endif //RACE_H
