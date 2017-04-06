//
// Created by pawel on 05.04.17.
//

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>
#include <Entity.h>
#include <RectangleArea.h>
#include <MathUtil.h>
#include <RectangleParams.h>

sf::Vector2f RectangleArea::b2VectorToSFML(const b2Vec2 &vec) {
    return sf::Vector2f(vec.x * 30, vec.y * 30);
}

void RectangleArea::Draw(sf::RenderWindow *window) {
    window->draw(rectangleShape_);
}

void RectangleArea::CreateB2Rectangle(const b2Vec2 &position, const b2Vec2 &
size, float angle, Entity *userData) {
    b2BodyDef bodyDef;
    //bodyDef.position = position;
    body_ = world_->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2, position, angle); // is center

    fixtureDef.shape = &polygonShape;
    fixtureDef.isSensor = true;

    b2Fixture *checkPointFixture = body_->CreateFixture(&fixtureDef);
    body_->SetUserData(userData);
}

void RectangleArea::CreateSFMLRectangle(const sf::Vector2f &position,
                                        const sf::Vector2f &size,
                                        float angle) {
    /**rectangleShape_ = sf::RectangleShape(b2VectorToSFML(size));
    sf::Vector2f convertedPos = b2VectorToSFML(position);
    convertedPos.x -= size.x * 30 / 2;
    convertedPos.y -= size.y * 30 / 2;

    rectangleShape_.setPosition(convertedPos);
    rectangleShape_.setRotation(30); */
    rectangleShape_ = sf::RectangleShape(size);
    rectangleShape_.setPosition(position);
    rectangleShape_.setRotation(angle);
}


RectangleArea::RectangleArea(b2World* world, const struct RectangleParams
&params, Entity *userData) : world_(world) {
    CreateB2Rectangle(params.b2Pos, params.b2Size, params.b2Angle, userData);
    CreateSFMLRectangle(params.sfmlPos, params.sfmlSize, params.sfmlAngle);
}

RectangleArea::~RectangleArea() {}

