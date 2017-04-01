/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#include "Map.h"
#include <cstdio>
#include <SFML/Window.hpp>

Map::Map() {
}

Map::~Map() {

}

void Map::LoadMap(const std::string &name, const std::string &full_name) {
    max_size = sf::Texture::getMaximumSize();
    printf("Maximum texture size on this GPU is %d\n", max_size);
    printf("Loading map %s...\n", name.c_str());
    std::string path("../resource/maps/");
    std::string name_view("/view.png");
    std::string name_friction("/friction.png");

    image_view.loadFromFile(path + name + name_view);
    map_view.loadFromImage(image_view);
    image_friction.loadFromFile(path + name + name_friction);
    map_friction.loadFromImage(image_friction);
    this->name = name;
    this->full_name = full_name;

    sprite_map.setTexture(map_view);
    sprite_friction.setTexture(map_friction);
    printf("Loading map %s done!\n", name.c_str());

    sf::Vector2u image_size = image_friction.getSize();
    minimap.reset(sf::FloatRect(0,0, image_size.x, image_size.y));
    minimap.setViewport(sf::FloatRect(0, 0, 0.3f, 0.3f));
    camera.setCenter(300,300);
    camera.setSize(1200,800);
    camera.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
}

const sf::Drawable &Map::GetViewMap() {
    return sprite_map;
}

float Map::GetFrictionModifier(const sf::Vector2f &pos) {

    unsigned int x = (unsigned int) (pos.x < 0 ? 0 : pos.x);
    unsigned int y = (unsigned int) (pos.y < 0 ? 0 : pos.y);
    sf::Color color = image_friction.getPixel(x, y);
    return 1.f - (color.b + color.r + color.g) / 256.0f / 3.0f;
}

const sf::Drawable &Map::GetFrictionMap() {
    return sprite_friction;
}

void Map::AlignCameraViewSize(const sf::Window &window) {
    sf::Vector2u wnd_size = window.getSize();
    camera.setSize(wnd_size.x, wnd_size.y);
}

const sf::View &Map::GetCameraView() {
    return camera;
}

const sf::View &Map::GetMinimapView() {
    return minimap;
}

void Map::SetCameraViewPosition(const sf::Vector2f &pos) {
    sf::Vector2f margin = camera.getSize();
    margin = margin / 2.0f;
    sf::Vector2u map_size = image_view.getSize();
    sf::Vector2f new_pos = pos;
    new_pos.x = (pos.x < margin.x ? margin.x : pos.x);
    new_pos.x = (pos.x > map_size.x - margin.x ? map_size.x - margin.x : new_pos.x);
    new_pos.y = (pos.y < margin.y ? margin.y : pos.y);
    new_pos.y = (pos.y > map_size.y - margin.y ? map_size.y - margin.y : new_pos.y);
    camera.setCenter(new_pos);
}

void Map::SetCameraViewZoom(float f) {
    camera.zoom(f);
}
