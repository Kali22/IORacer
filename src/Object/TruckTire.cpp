#include <Tools/MathUtil.h>
#include "TruckTire.h"

TruckTire::TruckTire(b2World *world, int x, int y, int angle, float scale) : scale_(scale) {
    sprite_.setTexture(GetTexture());
    sprite_.setOrigin(tireSize_ / 2, tireSize_ / 2);

    InitializeBody(world, x, y, angle);
    InitializeFixture();
}

void TruckTire::InitializeBody(b2World *world, int x, int y, int angle) {
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / scale_, y / scale_);
    bodyDef.angle = MathUtil::DegreeToRadian(angle);
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 1.0f;
    bodyDef.linearDamping = 2.0f;
    body_ = world->CreateBody(&bodyDef);
    body_->SetUserData(this);
}

void TruckTire::InitializeFixture() {
    b2CircleShape Shape;
    Shape.m_radius = (tireSize_ / 2) / scale_;
    b2FixtureDef FixtureDef;
    FixtureDef.density = 10.f;
    FixtureDef.friction = 0.2f;
    FixtureDef.restitution = 0.4f;
    FixtureDef.shape = &Shape;
    body_->CreateFixture(&FixtureDef);
}

static sf::Texture TruckTire::GetTexture() {
    if (!loaded_) {
        tireTexture_.loadFromFile("../resource/truckTire.png");
        loaded_ = true;
    }
    return tireTexture_;
}

void TruckTire::draw(sf::RenderWindow *window) {
    sprite_.setPosition(body_->GetPosition().x * scale_, body_->GetPosition().y * scale_);
    sprite_.setRotation(MathUtil::RadianToDegree(body_->GetAngle()));
    window->draw(sprite_);
}

int TruckTire::GetEntityType() const {
    return STATIC_TIRE;
}