/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <Tire.h>
#include <Dynamics/b2World.h>
#include <Collision/Shapes/b2PolygonShape.h>
#include <Tools/MathUtil.h>
#include <TireControlE.h>

int Tire::GetEntityType() const {
    return TIRE;
}

Tire::Tire(b2World *world, float scale) {//}, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = b2_pi / 2;
    bodyDef.position = b2Vec2(100, 100);
    body = world->CreateBody(&bodyDef);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox((6.f / 2.f) / scale, (12.f / 2.f) / scale);
    body->CreateFixture(&polygonShape, 2.f);//shape, density
    body->SetUserData(this);
    tireTexture.loadFromFile("../resource/tire.png");
    tireSprite.setTexture(tireTexture);
    tireSprite.setOrigin(3.f, 6.f);
    maxLateralImpulse = 0.91f;
}

Tire::~Tire() {
    body->GetWorld()->DestroyBody(body);
}

b2Vec2 Tire::GetLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

void Tire::UpdateFriction(float mod, CarParameters &params) {
    b2Vec2 impulse = body->GetMass() * -GetLateralVelocity();
    if (impulse.Length() > 5 * mod * maxLateralImpulse)
        impulse *= 5 * mod * maxLateralImpulse / impulse.Length();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    body->ApplyAngularImpulse(0.5f * body->GetInertia() * -body->GetAngularVelocity(), true);
    b2Vec2 currentForwardNormal = GetForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -(1.0f - mod + 0.15f) * 0.2f * currentForwardSpeed;
    body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

void Tire::Render(sf::RenderWindow &window) {
    tireSprite.setPosition(30.0f * body->GetPosition().x,
                           30.0f * body->GetPosition().y);
    tireSprite.setRotation(MathUtil::RadianToDegree(body->GetAngle()));
    window.draw(tireSprite);
}

b2Vec2 Tire::GetForwardVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

void Tire::UpdateDrive(int state, float mod, CarParameters &params) {
    //find desired speed
    float desiredSpeed = 0;
    switch (state & (UP | DOWN)) {
        case UP:
            desiredSpeed = params.maxForwardSpeed;
            break;
        case DOWN:
            desiredSpeed = params.maxBackwardSpeed;
            break;
        default:
            return;//do nothing
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (desiredSpeed > currentSpeed)
        force = params.maxEnginePower;
    else if (desiredSpeed < currentSpeed)
        force = -params.maxEnginePower;
    else
        return;
    body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter(), true);
}

void Tire::Reset() {
    body->SetLinearDamping(0);
    body->SetAngularDamping(0);
    body->SetAngularVelocity(0);
    body->SetLinearVelocity(b2Vec2(0, 0));
}
