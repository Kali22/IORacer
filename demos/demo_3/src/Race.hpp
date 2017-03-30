//
// Created by pawel on 30.03.17.
//

#ifndef RACE_H

#include <SFML/Graphics.hpp>

class Race {
public:
    Race(sf::RenderWindow& win) : window(win) { }

    void Run();
private:
    sf::RenderWindow& window;
};

#endif //RACE_H
