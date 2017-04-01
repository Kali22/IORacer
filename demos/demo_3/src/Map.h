/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#ifndef _Map_H_
#define _Map_H_

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Map {
private:
    std::string name;
    std::string full_name;
    sf::Texture map_view;   //!< Visual part, in GPU memory
    sf::Image image_view;   //!< Visual part, in CPU memory
    sf::Texture map_friction; //!< Friction modulator map, in GPU memory
    sf::Image image_friction;   //!< Friction modulator map, in CPU memory
    sf::Sprite map_sprite;

public:
    Map();
    ~Map();
    void LoadMap(const std::string& name, const std::string &full_name);

    const sf::Drawable &GetViewMap();
    float GetFrictionModifier(const sf::Vector2f &pos);
};


#endif //Map
