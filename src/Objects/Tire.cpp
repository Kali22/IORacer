/**
 *  @file
 *  @ingroup tire
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include "Tire.h"
#include <Dynamics/b2World.h>
#include <Collision/Shapes/b2PolygonShape.h>
#include <MathUtil.h>
#include <TireControlE.h>

int Tire::GetObjectType() const {
    return TIRE;
}

Tire::Tire(b2World *world, VisualObjectPtr visualObject)
        : Object(InitializeBody(world, visualObject->GetSize()), visualObject),
          maxTireFrictionForce_(1.51f) {
    body_->SetUserData(this);
}

b2Body* Tire::InitializeBody(b2World *world, const RealVec& size) {
    b2BodyDef body_Def;
    body_Def.type = b2_dynamicBody;
    b2Body *body = world->CreateBody(&body_Def);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2);
    body->CreateFixture(&polygonShape, 2.f);//shape, density
    return body;
}

Tire::~Tire() {
    body_->GetWorld()->DestroyBody(body_);
}

b2Vec2 Tire::GetLateralVelocity() {
    b2Vec2 currentRightNormal = body_->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body_->GetLinearVelocity()) *
           currentRightNormal;
}

void Tire::UpdateFriction(float mod) {
    if (locked_) {
        UpdateFrictionLocked(mod);
    } else {
        UpdateFrictionNotLocked(mod);
    }
}

void Tire::UpdateFrictionLocked(float mod) {
    b2Vec2 impulse =
            body_->GetMass() * -(GetLateralVelocity() + GetForwardVelocity());
    if (impulse.Length() > mod * maxTireFrictionForce_)
        impulse *= mod * maxTireFrictionForce_ / impulse.Length();

    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
    body_->ApplyAngularImpulse(
            0.5f * body_->GetInertia() * -body_->GetAngularVelocity(), true);
}

void Tire::UpdateFrictionNotLocked(float mod) {
    b2Vec2 impulse = body_->GetMass() * -GetLateralVelocity();
    if (impulse.Length() > mod * maxTireFrictionForce_)
        impulse *= mod * maxTireFrictionForce_ / impulse.Length();

    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
    body_->ApplyAngularImpulse(
            0.5f * body_->GetInertia() * -body_->GetAngularVelocity(), true);

    b2Vec2 currentForwardNormal = GetForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude =
            -(1.0f - mod + 0.25f) * 0.2f * currentForwardSpeed;
    body_->ApplyForce(dragForceMagnitude * currentForwardNormal,
                     body_->GetWorldCenter(), true);
}

b2Vec2 Tire::GetForwardVelocity() {
    b2Vec2 currentRightNormal = body_->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentRightNormal, body_->GetLinearVelocity()) *
           currentRightNormal;
}

void Tire::UpdateDrive(int state, float mod, CarParametersPtr params) {
    locked_ = (bool) (state & BRAKE);
    if (locked_) {
        return;
    }

    float desiredSpeed = GetDesiredSpeed(state, params);
    if (desiredSpeed == 0) {
        return;
    }

    b2Vec2 currentForwardNormal = body_->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(GetForwardVelocity(), currentForwardNormal);

    float force = GetForce(currentSpeed, desiredSpeed, params);
    body_->ApplyForce(/*mod * */force * currentForwardNormal,
                               body_->GetWorldCenter(), true);
}

float Tire::GetDesiredSpeed(int state, CarParametersPtr params) {
    if (state & UP) {
        return params->maxForwardSpeed;
    } else if (state & DOWN) {
        return params->maxBackwardSpeed;
    } else {
        return 0;
    }
}

float Tire::GetForce(float currentSpeed, float desiredSpeed,
                           CarParametersPtr params) {
    float force = params->maxEnginePower;
    if (desiredSpeed > currentSpeed)
        return force;
    else if (desiredSpeed < currentSpeed)
        return -force;
    else
        return 0;
}

void Tire::Reset(float x, float y) {
    body_->SetAngularVelocity(0);
    body_->SetLinearVelocity(b2Vec2(0, 0));
    body_->SetTransform(b2Vec2(x, y), b2_pi / 2);
}

void Tire::InitializeTire(b2World *world, b2RevoluteJoint **jointPtr,
                             b2RevoluteJointDef &jointDef,
                             float bodyOffSetX, float bodyOffSetY,
                             TirePositionE positionFlag) {
    tirePosition_ = positionFlag;
    jointDef.bodyB = body_;
    jointDef.localAnchorA.Set(bodyOffSetX / 30, bodyOffSetY / 30);
    *jointPtr = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
}

bool Tire::IsLeft() const {
    return tirePosition_ == LEFT_FRONT_TIRE || tirePosition_ == LEFT_REAR_TIRE;
}

bool Tire::IsFront() const {
    return tirePosition_ == LEFT_FRONT_TIRE || tirePosition_ == RIGHT_FRONT_TIRE;
}
