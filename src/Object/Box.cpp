#include "Box.h"

#define SCALE 30.f

Box::Box(b2World *world, int x, int y, int angle) {
    // SFML
    static sf::Texture boxTexture;
    static bool loaded = false;
    static float boxSize;
    if (!loaded) {
        boxTexture.loadFromFile("../resource/box.png");
        loaded = true;
    }

    sprite.setTexture(boxTexture);
    sprite.setOrigin(boxSize / 2, boxSize / 2);

    // Box2D
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
    bodyDef.angle = angle * b2_pi / 180.f;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 1.0f;
    bodyDef.linearDamping = 1.0f;
    body = world->CreateBody(&bodyDef);
    body->SetUserData(this);

    b2PolygonShape Shape;
    Shape.SetAsBox((boxSize / 2) / SCALE, (boxSize / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 5.f;
    FixtureDef.friction = 0.5f;
    FixtureDef.restitution = 0.4f;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);
}

void Box::draw(sf::RenderWindow *window) {
    sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
    sprite.setRotation(body->GetAngle()  * 180.f / b2_pi);
    window->draw(sprite);
}

int Box::GetEntityType() const {
    return BOX;
}






