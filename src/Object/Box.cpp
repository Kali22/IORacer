#include <iostream>
#include "Box.h"

Box::Box(b2World *world, int x, int y, int angle, float scale) {
    // SFML
    static sf::Texture boxTexture;
    static bool loaded = false;
    static float boxSize = 48.f;
    scale_ = scale;
    if (!loaded) {
        boxTexture.loadFromFile("../resource/box.png");
        loaded = true;
    }

    sprite_.setTexture(boxTexture);
    sprite_.setOrigin(boxSize / 2, boxSize / 2);

    // Box2D
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / scale, y / scale);
    bodyDef.angle = angle * b2_pi / 180.f;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 1.0f;
    bodyDef.linearDamping = 2.0f;
    body_ = world->CreateBody(&bodyDef);
    body_->SetUserData(this);

    b2PolygonShape Shape;
    Shape.SetAsBox((boxSize / 2) / scale, (boxSize / 2) / scale);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 5.f;
    FixtureDef.friction = 0.5f;
    FixtureDef.restitution = 0.4f;
    FixtureDef.shape = &Shape;
    body_->CreateFixture(&FixtureDef);
}

void Box::draw(sf::RenderWindow *window) {
    sprite_.setPosition(body_->GetPosition().x * scale_, body_->GetPosition().y * scale_);
    sprite_.setRotation(body_->GetAngle()  * 180.f / b2_pi);
    window->draw(sprite_);
}

int Box::GetEntityType() const {
    return BOX;
}






