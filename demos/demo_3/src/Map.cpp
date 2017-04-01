/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#include "Map.h"
#include <cstdio>

Map::Map() {

}

Map::~Map() {

}

void Map::LoadMap(const std::string &name, const std::string &full_name) {
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

    map_sprite.setTexture(map_view);
    printf("Loading map %s done!\n", name.c_str());
}

const sf::Drawable &Map::GetViewMap() {
    return map_sprite;
}

float Map::GetFrictionModifier(const sf::Vector2f &pos) {

    unsigned int x = (unsigned int) (pos.x < 0 ? 0 : pos.x);
    unsigned int y = (unsigned int) (pos.y < 0 ? 0 : pos.y);
    sf::Color color = image_friction.getPixel(x, y);
    return 1.f - (color.b + color.r + color.g) / 256.0f / 3.0f;
}
