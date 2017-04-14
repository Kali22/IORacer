/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <Dynamics/b2World.h>
#include <Collision/Shapes/b2PolygonShape.h>
#include <TireControlE.h>
#include <Vehicle/Tire.h>
#include "Tire.h"

#define SCALE 30.f

int Tire::GetEntityType() const {
    return TIRE;
}

Tire::Tire(b2World *world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = 0;
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox((6.f / 2.f) / SCALE, (12.f / 2.f) / SCALE);
    body->CreateFixture(&polygonShape, 2.f);//shape, density
    body->SetUserData(this);
    tireTexture.loadFromFile("../resource/tire.png");
    tireSprite.setTexture(tireTexture);
    tireSprite.setOrigin(3.f, 6.f);
    maxTireFrictionForce_ = 0.91;
}

Tire::~Tire() {
    body->GetWorld()->DestroyBody(body);
}

b2Vec2 Tire::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;

}

void Tire::UpdateFriction(float mod) {
    if (locked_) {
        b2Vec2 impulse = body->GetMass() * -(getLateralVelocity() + getForwardVelocity());
        if (impulse.Length() > 5 * mod * maxTireFrictionForce_)
            impulse *= 5 * mod * maxTireFrictionForce_ / impulse.Length();
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
        body->ApplyAngularImpulse(0.5f * body->GetInertia() * -body->GetAngularVelocity(), true);
    } else {
        b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
        if (impulse.Length() > 5 * mod * maxTireFrictionForce_)
            impulse *= 5 * mod * maxTireFrictionForce_ / impulse.Length();
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
        body->ApplyAngularImpulse(0.5f * body->GetInertia() * -body->GetAngularVelocity(), true);
        b2Vec2 currentForwardNormal = getForwardVelocity();
        float currentForwardSpeed = currentForwardNormal.Normalize();
        float dragForceMagnitude = -(1.0f - mod + 0.15f) * 0.2f * currentForwardSpeed;
        body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
    }
}

void Tire::Render(sf::RenderWindow &window) {
    tireSprite.setPosition(30.0f * body->GetPosition().x,
                           30.0f * body->GetPosition().y);
    tireSprite.setRotation(body->GetAngle() * 180.f / b2_pi);
    window.draw(tireSprite);
}

b2Vec2 Tire::getForwardVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

void Tire::UpdateDrive(int state, float mod) {
    //find desired speed
    float desiredSpeed = 0;
    locked_ = false;
    switch (state & (UP | DOWN)) {
        case UP:
            desiredSpeed = 30;
            break;
        case DOWN:
            desiredSpeed = -20;
            break;
        case BRAKE:
            locked_ = true;
        default:
            return;//do nothing
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (desiredSpeed > currentSpeed)
        force = 10;
    else if (desiredSpeed < currentSpeed)
        force = -10;
    else
        return;

    if (!locked_)
        body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter(), true);
}
