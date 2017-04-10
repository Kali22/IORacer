#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>
#include <Tools/Entity.h>
#include <Tools/RectangleArea.h>

RectangleArea::RectangleArea(b2World *world, const struct RectangleParams &params) : world_(world) {
    CreateB2Rectangle(params.b2Pos, params.b2Size, params.b2Angle);
    CreateSFMLRectangle(params.sfmlPos, params.sfmlSize, params.sfmlAngle);
}

RectangleArea::~RectangleArea() {}

void RectangleArea::Draw(sf::RenderWindow *window) const {
    window->draw(rectangleShape_);
}

void RectangleArea::SetCollisionUserData(Entity *entity) {
    body_->SetUserData(entity);
}

void RectangleArea::CreateB2Rectangle(const b2Vec2 &position, const b2Vec2 &size, float angle) {
    b2BodyDef bodyDef;
    body_ = world_->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2, position, angle); // is center

    fixtureDef.shape = &polygonShape;
    fixtureDef.isSensor = true;

    b2Fixture *checkPointFixture = body_->CreateFixture(&fixtureDef);
}

void RectangleArea::CreateSFMLRectangle(const sf::Vector2f &position,
                                        const sf::Vector2f &size,
                                        float angle) {
    rectangleShape_ = sf::RectangleShape(size);
    rectangleShape_.setOrigin(size.x / 2, size.y / 2);
    rectangleShape_.move(position);
    rectangleShape_.setRotation(angle);
}

