/**
 *  @file
 *  @ingroup map
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#include "Map.h"
#include <Box2D.h>
#include <SFML/Window.hpp>

b2Body *CreateBox(b2World *World, float MouseX, float MouseY, float width, float height, float scale) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX / scale, MouseY / scale);
    BodyDef.type = b2_staticBody;
    b2Body *Body = World->CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((width / 2) / scale, (height / 2) / scale);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    return Body;
}

Map::Map(b2World *world, float scale, sf::Vector2f startPosition)
        : world_(world), scale_(scale), startPosition_(startPosition) {
    for (int i = 0; i < 4; ++i)
        bands_[i] = nullptr;
}

sf::Vector2f Map::GetStartPosition() {
    return startPosition_;
}

Map::~Map() {
    for (int i = 0; i < 4; ++i)
        if (bands_[i]) {
            bands_[i]->GetWorld()->DestroyBody(bands_[i]);
            bands_[i] = nullptr;
        }
    printf("Map %s destroyed!\n", name_.c_str());
}

void Map::LoadMap(const std::string &name, const std::string &full_name) {
    max_size_ = sf::Texture::getMaximumSize();
    printf("Maximum texture size on this GPU is %d\n", max_size_);
    printf("Loading map %s...\n", name.c_str());
    std::string path("../resource/maps/");
    std::string name_view("/view.png");
    std::string name_friction("/friction.png");

    image_view_.loadFromFile(path + name + name_view);
    map_view_.loadFromImage(image_view_);
    image_friction_.loadFromFile(path + name + name_friction);
    map_friction_.loadFromImage(image_friction_);
    this->name_ = name;
    this->full_name_ = full_name;

    sprite_map_.setTexture(map_view_);
    sprite_friction_.setTexture(map_friction_);
    printf("Loading map %s done!\n", name.c_str());

    sf::Vector2u image_size = image_friction_.getSize();
    minimap_.reset(sf::FloatRect(0, 0, image_size.x, image_size.y));
    minimap_.setViewport(sf::FloatRect(0, 0, 0.3f, 0.3f));
    camera_.setCenter(300, 300);
    camera_.setSize(1200, 800);
    camera_.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

    bands_[0] = CreateBox(world_, image_size.x / 2.f, 0, image_size.x + 10.f, 10.f, scale_);
    bands_[1] = CreateBox(world_, image_size.x / 2.f, image_size.y, image_size.x + 10.f, 10.f, scale_);
    bands_[2] = CreateBox(world_, 0, image_size.y / 2.f, 10.f, image_size.y + 10.f, scale_);
    bands_[3] = CreateBox(world_, image_size.x, image_size.y / 2.f, 10.f, image_size.y + 10.f, scale_);
    for (int i = 0; i < 4; ++i) {
        bands_sprite_[i].setOrigin(0, 0);
        bands_sprite_[i].setTextureRect(sf::IntRect(0, 0, image_size.x, 10));
        bands_sprite_[i].setTexture(map_friction_);
    }
    bands_sprite_[0].setPosition(0, 0);
    bands_sprite_[1].setPosition(image_size.x, 0);
    bands_sprite_[1].setRotation(90);
    bands_sprite_[2].setPosition(0, image_size.y - 10);
    bands_sprite_[3].setPosition(10, 0);
    bands_sprite_[3].setRotation(90);

}

const sf::Drawable &Map::GetViewMap() {
    return sprite_map_;
}

float Map::GetFrictionModifier(const sf::Vector2f &pos) {
    unsigned int x = (unsigned int) (pos.x < 0 ? 0 : pos.x);
    unsigned int y = (unsigned int) (pos.y < 0 ? 0 : pos.y);
    sf::Color color = image_friction_.getPixel(x, y);
    return 1.f - (color.b + color.r + color.g) / 256.0f / 3.0f;
}

const sf::Drawable &Map::GetFrictionMap() {
    return sprite_friction_;
}

void Map::AlignCameraViewSize(const sf::Window &window) {
    sf::Vector2u wnd_size = window.getSize();
    camera_.setSize(wnd_size.x, wnd_size.y);
}

const sf::View &Map::GetCameraView() {
    return camera_;
}

const sf::View &Map::GetMinimapView() {
    return minimap_;
}

void Map::SetCameraViewPosition(const sf::Vector2f &pos) {
    sf::Vector2f margin = camera_.getSize();
    margin = margin / 2.0f;
    sf::Vector2u map_size = image_view_.getSize();
    sf::Vector2f new_pos = pos;
    new_pos.x = (pos.x < margin.x ? margin.x : pos.x);
    new_pos.x = (pos.x > map_size.x - margin.x ? map_size.x - margin.x : new_pos.x);
    new_pos.y = (pos.y < margin.y ? margin.y : pos.y);
    new_pos.y = (pos.y > map_size.y - margin.y ? map_size.y - margin.y : new_pos.y);
    camera_.setCenter(new_pos);
}

void Map::SetCameraViewZoom(float f) {
    camera_.zoom(f);
}

void Map::RenderBottomLayer(sf::RenderWindow &window) {
    window.setView(camera_);
    window.draw(sprite_map_);
    window.draw(bands_sprite_[0]);
    window.draw(bands_sprite_[1]);
    window.draw(bands_sprite_[2]);
    window.draw(bands_sprite_[3]);
    window.setView(window.getDefaultView());
}
