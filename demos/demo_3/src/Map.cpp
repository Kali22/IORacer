/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#include "Map.h"
#include <cstdio>
#include <Box2D.h>
#include <SFML/Window.hpp>


#define SCALE 30.f

b2Body *CreateBox(b2World &World, float MouseX, float MouseY, float width, float height) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
    BodyDef.type = b2_staticBody;
    b2Body *Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    return Body;
}

Map::Map(b2World &world) : world(world) {
    for (int i = 0; i < 4; ++i)
        bands[i] = NULL;
}

Map::~Map() {
    for (int i = 0; i < 4; ++i)
        if (bands[i])
            world.DestroyBody(bands[i]);
    printf("Map %s destroyed!\n", name.c_str());
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
    minimap.reset(sf::FloatRect(0, 0, image_size.x, image_size.y));
    minimap.setViewport(sf::FloatRect(0, 0, 0.3f, 0.3f));
    camera.setCenter(300, 300);
    camera.setSize(1200, 800);
    camera.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

    bands[0] = CreateBox(world, image_size.x / 2.f, 0, image_size.x + 10.f, 10.f);
    bands[1] = CreateBox(world, image_size.x / 2.f, image_size.y, image_size.x + 10.f, 10.f);
    bands[2] = CreateBox(world, 0, image_size.y / 2.f, 10.f, image_size.y + 10.f);
    bands[3] = CreateBox(world, image_size.x, image_size.y / 2.f, 10.f, image_size.y + 10.f);
    for (int i = 0; i < 4; ++i) {
        bands_sprite[i].setOrigin(0,0);
        bands_sprite[i].setTextureRect(sf::IntRect(0,0,image_size.x,10));
        bands_sprite[i].setTexture(map_friction);
    }
    bands_sprite[0].setPosition(0,0);
    bands_sprite[1].setPosition(image_size.x,0);
    bands_sprite[1].setRotation(90);
    bands_sprite[2].setPosition(0,image_size.y - 10);
    bands_sprite[3].setPosition(10,0);
    bands_sprite[3].setRotation(90);

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
    camera.setSize(wnd_size.x / 2.5f, wnd_size.y / 2.5f);
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

void Map::RenderBottomLayer(sf::RenderWindow &window) {
    window.setView(camera);
    window.draw(sprite_map);
    window.draw(bands_sprite[0]);
    window.draw(bands_sprite[1]);
    window.draw(bands_sprite[2]);
    window.draw(bands_sprite[3]);
    window.setView(window.getDefaultView());
}
