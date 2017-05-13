#include <MathUtil.h>
#include "TruckTire.h"

TruckTire::TruckTire(b2World *world, VisualObjectPtr visualObject)
        : Object(InitializeBody(world, visualObject->GetSize()), visualObject) {
    body_->SetUserData(this);
}

b2Body* TruckTire::InitializeBody(b2World *world, const RealVec& size) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 1.0f;
    bodyDef.linearDamping = 2.0f;
    b2Body* body = world->CreateBody(&bodyDef);
    InitializeFixture(body, size);
    return body;
}

void TruckTire::InitializeFixture(b2Body* body, const RealVec& size) {
    b2CircleShape Shape;
    Shape.m_radius = size.x / 2;
    b2FixtureDef FixtureDef;
    FixtureDef.density = 10.f;
    FixtureDef.friction = 0.2f;
    FixtureDef.restitution = 0.4f;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);
}

int TruckTire::GetObjectType() const {
    return STATIC_TIRE;
}