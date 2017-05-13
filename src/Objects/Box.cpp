#include <iostream>
#include <MathUtil.h>
#include "Box.h"

Box::Box(b2World *world, VisualObjectPtr visualObject)
        : Object(InitializeBody(world, visualObject->GetSize()),
                       visualObject) {
    body_->SetUserData(this);
}

b2Body* Box::InitializeBody(b2World *world, const RealVec& size) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 1.0f;
    bodyDef.linearDamping = 2.0f;
    b2Body* body = world->CreateBody(&bodyDef);
    InitializeFixture(body, size);
    return body;
}

void Box::InitializeFixture(b2Body* body, const RealVec& size) {
    b2PolygonShape Shape;
    Shape.SetAsBox(size.x / 2, size.y / 2);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 5.f;
    FixtureDef.friction = 0.5f;
    FixtureDef.restitution = 0.3f;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);
}

int Box::GetObjectType() const {
    return BOX;
}
