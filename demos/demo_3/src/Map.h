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
#include <SFML/Graphics/View.hpp>
#include <Dynamics/b2Body.h>
#include <Dynamics/b2World.h>
#include <SFML/Graphics/RenderWindow.hpp>

class Map {
private:
    unsigned int max_size;
    std::string name;
    std::string full_name;
    sf::Texture map_view;   //!< Visual part, in GPU memory
    sf::Image image_view;   //!< Visual part, in CPU memory
    sf::Texture map_friction; //!< Friction modulator map, in GPU memory
    sf::Image image_friction;   //!< Friction modulator map, in CPU memory
    sf::Sprite sprite_map;
    sf::Sprite sprite_friction;

    sf::View camera;
    sf::View minimap;

    b2World *world;
    b2Body *bands[4]; //!< Outside bands
    sf::Sprite bands_sprite[4];

public:
    Map(b2World *world);
    ~Map();
    void LoadMap(const std::string& name, const std::string &full_name);
    float GetFrictionModifier(const sf::Vector2f &pos);

    const sf::Drawable &GetViewMap();
    const sf::Drawable &GetFrictionMap();
    const sf::View &GetCameraView();
    const sf::View &GetMinimapView();
    
    void AlignCameraViewSize(const sf::Window &window);
    void SetCameraViewPosition(const sf::Vector2f &pos);
    void SetCameraViewZoom(float f);

    void RenderBottomLayer(sf::RenderWindow &window);
};


#endif //Map
