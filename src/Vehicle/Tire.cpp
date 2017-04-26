/**
 *  @file
 *  @ingroup tire
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

Tire::Tire(b2World *world, float scale, float x, float y, CarParametersPtr carParameters, TirePositionE positionFlags)
        : carParameters_(carParameters), tirePosition_(positionFlags) {
    InitializeBody(world, scale, x, y);
    tireTexture.loadFromFile("../resource/tire.png");
    tireSprite.setTexture(tireTexture);
    tireSprite.setOrigin(3.f, 6.f);
    maxTireFrictionForce_ = 1.51f;
}

void Tire::InitializeBody(b2World *world, float scale, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = b2_pi / 2;
    bodyDef.position = b2Vec2(x / scale, y / scale);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox((6.f / 2.f) / scale, (12.f / 2.f) / scale);
    body->CreateFixture(&polygonShape, 2.f);//shape, density
    body->SetUserData(this);
}

Tire::~Tire() {
    body->GetWorld()->DestroyBody(body);
}

b2Vec2 Tire::GetLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

void Tire::UpdateFriction(float mod) {
    if (locked_) {
        UpdateFrictionLocked(mod);
    } else {
        UpdateFrictionNotLocked(mod);
    }
}

void Tire::UpdateFrictionLocked(float mod) {
    b2Vec2 impulse = body->GetMass() * -(GetLateralVelocity() + GetForwardVelocity());
    if (impulse.Length() > mod * maxTireFrictionForce_)
        impulse *= mod * maxTireFrictionForce_ / impulse.Length();

    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    body->ApplyAngularImpulse(0.5f * body->GetInertia() * -body->GetAngularVelocity(), true);
}

void Tire::UpdateFrictionNotLocked(float mod) {
    b2Vec2 impulse = body->GetMass() * -GetLateralVelocity();
    if (impulse.Length() > mod * maxTireFrictionForce_)
        impulse *= mod * maxTireFrictionForce_ / impulse.Length();

    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    body->ApplyAngularImpulse(0.5f * body->GetInertia() * -body->GetAngularVelocity(), true);

    b2Vec2 currentForwardNormal = GetForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -(1.0f - mod + 0.25f) * 0.2f * currentForwardSpeed;
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

void Tire::UpdateDrive(int state, float mod) {
    locked_ = (bool) (state & BRAKE);
    if (locked_) {
        return;
    }

    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);
    float desiredSpeed = GetDesiredSpeed(state);

    float force = GetNecessaryForce(currentSpeed, desiredSpeed);
    body->ApplyForce(/*mod * */force * currentForwardNormal, body->GetWorldCenter(), true);
}

float Tire::GetDesiredSpeed(int state) {
    if (state & UP) {
        return carParameters_->maxForwardSpeed;
    } else if (state & DOWN) {
        return carParameters_->maxBackwardSpeed;
    } else {
        return 0;
    }
}

float Tire::GetNecessaryForce(float currentSpeed, float desiredSpeed) {
    float force = carParameters_->maxEnginePower;
    if (desiredSpeed > currentSpeed)
        return force;
    else if (desiredSpeed < currentSpeed)
        return -force;
    else
        return 0;
}

void Tire::Reset(float x, float y) {
    body->SetAngularVelocity(0);
    body->SetLinearVelocity(b2Vec2(0, 0));
    body->SetTransform(b2Vec2(x, y), b2_pi / 2);
}

bool Tire::IsLeft() const {
    return tirePosition_ == LEFT_FRONT_TIRE || tirePosition_ == LEFT_REAR_TIRE;
}

bool Tire::IsFront() const {
    return tirePosition_ == LEFT_FRONT_TIRE || tirePosition_ == RIGHT_FRONT_TIRE;
}
