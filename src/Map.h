/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#pragma once

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <Dynamics/b2Body.h>
#include <Dynamics/b2World.h>
#include <SFML/Graphics/RenderWindow.hpp>

class Map {
public:
    Map(b2World *world, float scale, sf::Vector2f startPosition);

    ~Map();

    void LoadMap(const std::string &name, const std::string &full_name);

    float GetFrictionModifier(const sf::Vector2f &pos);

    const sf::Drawable &GetViewMap();

    const sf::Drawable &GetFrictionMap();

    const sf::View &GetCameraView();

    const sf::View &GetMinimapView();

    void AlignCameraViewSize(const sf::Window &window);

    void SetCameraViewPosition(const sf::Vector2f &pos);

    void SetCameraViewZoom(float f);

    void RenderBottomLayer(sf::RenderWindow &window);

    sf::Vector2f GetStartPosition();

private:
    float scale_;
    sf::Vector2f startPosition_;
    unsigned int max_size_;
    std::string name_;
    std::string full_name_;
    sf::Texture map_view_;   //!< Visual part, in GPU memory
    sf::Image image_view_;   //!< Visual part, in CPU memory
    sf::Texture map_friction_; //!< Friction modulator map, in GPU memory
    sf::Image image_friction_;   //!< Friction modulator map, in CPU memory
    sf::Sprite sprite_map_;
    sf::Sprite sprite_friction_;

    sf::View camera_;
    sf::View minimap_;

    b2World *world_;
    b2Body *bands_[4]; //!< Outside bands
    sf::Sprite bands_sprite_[4];
};
