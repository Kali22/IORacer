#include "TruckTire.h"

TruckTire::TruckTire(b2World *world, int x, int y, int angle, float scale) {
    // SFML
    static sf::Texture tireTexture;
    static bool loaded = false;
    static float tireSize = 64.f;
    scale_ = scale;
    if (!loaded) {
        tireTexture.loadFromFile("../resource/box.png");
        loaded = true;
    }

    sprite_.setTexture(tireTexture);
    sprite_.setOrigin(tireSize / 2, tireSize / 2);

    // Box2D
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / scale, y / scale);
    bodyDef.angle = angle * b2_pi / 180.f;
    bodyDef.type = b2_staticBody;
    body_ = world->CreateBody(&bodyDef);
    body_->SetUserData(this);

    b2PolygonShape Shape;
    Shape.SetAsBox((tireSize / 2) / scale, (tireSize / 2) / scale);
    b2FixtureDef FixtureDef;
    FixtureDef.friction = 0.2f;
    FixtureDef.restitution = 0.8f;
    FixtureDef.shape = &Shape;
    body_->CreateFixture(&FixtureDef);
}

void TruckTire::draw(sf::RenderWindow *window) {
    sprite_.setPosition(body_->GetPosition().x * scale_, body_->GetPosition().y * scale_);
    sprite_.setRotation(body_->GetAngle()  * 180.f / b2_pi);
    window->draw(sprite_);
}

int TruckTire::GetEntityType() const {
    return STATIC_TIRE;
}