#include <iostream>
#include <Tools/MathUtil.h>
#include "Box.h"

Box::Box(b2World *world, int x, int y, int angle, float scale) : scale_(scale) {
    // SFML
    sprite_.setTexture(GetTexture());
    sprite_.setOrigin(boxSize_ / 2, boxSize_ / 2);

    // Box2D
    InitializeBody(world, x, y, angle);
    InitializeFixture();
}

void Box::InitializeBody(b2World *world, int x, int y, int angle) {
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / scale_, y / scale_);
    bodyDef.angle = MathUtil::DegreeToRadian(angle);
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 1.0f;
    bodyDef.linearDamping = 2.0f;
    body_ = world->CreateBody(&bodyDef);
    body_->SetUserData(this);
}

void Box::InitializeFixture() {
    b2PolygonShape Shape;
    Shape.SetAsBox((boxSize_ / 2) / scale_, (boxSize_ / 2) / scale_);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 5.f;
    FixtureDef.friction = 0.5f;
    FixtureDef.restitution = 0.3f;
    FixtureDef.shape = &Shape;
    body_->CreateFixture(&FixtureDef);
}

static sf::Texture Box::GetTexture() const {
    if (!loaded_) {
        boxTexture_.loadFromFile("../resource/box.png");
        loaded_ = true;
    }
    return boxTexture_;
}

void Box::draw(sf::RenderWindow *window) {
    sprite_.setPosition(body_->GetPosition().x * scale_, body_->GetPosition().y * scale_);
    sprite_.setRotation(MathUtil::RadianToDegree(body_->GetAngle()));
    window->draw(sprite_);
}

int Box::GetEntityType() const {
    return BOX;
}






