#include "Wheel.h"

Wheel::Wheel(b2Body *body, VisualObjectPtr wheel) : Object(body, wheel, OBJECT_TYPE_WHEEL) {
    body_->SetUserData(this);
}

void Wheel::InitializeWheel(b2RevoluteJoint **jointPtr,
                            b2RevoluteJointDef &jointDef,
                            float bodyOffSetX,
                            float bodyOffSetY,
                            WheelPositionE positionFlag) {
    positionFlag_ = positionFlag;
    jointDef.bodyB = body_;
    jointDef.localAnchorA.Set(bodyOffSetX, bodyOffSetY);
    *jointPtr = (b2RevoluteJoint *) body_->GetWorld()->CreateJoint(&jointDef);
}

void Wheel::UpdateModifiers(float groundMod, float reactF, float vehicleAeroFriction) {
    frictionModifier_ = 50.f * groundMod;
    maxTireFrictionForce_ = groundMod * reactF * 300;
    vehicleAeroFriction_ = vehicleAeroFriction;
}

void Wheel::UpdateFriction(float dt) {
    if (locked_)
        UpdateFrictionLocked(dt);
    else
        UpdateFrictionNotLocked(dt);
}

bool Wheel::IsFront() const {
    return positionFlag_ == WHEEL_RIGHT_FRONT || positionFlag_ == WHEEL_LEFT_FRONT;
}

bool Wheel::IsLeft() const {
    return positionFlag_ == WHEEL_LEFT_FRONT || positionFlag_ == WHEEL_LEFT_REAR;
}

void Wheel::UpdateDrive(float torque, float dt) {
    if (!locked_) {
        b2Vec2 currentForwardNormal = body_->GetWorldVector(b2Vec2(0, 1));
        body_->ApplyForce(torque * wheelRadius_ * currentForwardNormal, body_->GetWorldCenter(), true);
    }
}

void Wheel::Reset(float x, float y, float angle) {
    body_->SetAngularVelocity(0);
    body_->SetLinearVelocity(b2Vec2(0, 0));
    body_->SetTransform(b2Vec2(x, y), angle);
}

Wheel::~Wheel() {
    body_->GetWorld()->DestroyBody(body_);
}

void Wheel::UpdateFrictionLocked(float dt) {
    b2Vec2 impulse = body_->GetMass() * -body_->GetLinearVelocity();
    if (impulse.Length() > dt * maxTireFrictionForce_* 100.)
        impulse *= dt * maxTireFrictionForce_ * 100./ impulse.Length();

    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
    body_->ApplyAngularImpulse(0.5f * body_->GetInertia() * -body_->GetAngularVelocity(), true);

    b2Vec2 currBodyVelDir = body_->GetLinearVelocity();
    float bodySpeed = currBodyVelDir.Normalize();
    float aeroForceMagnitude = -0.1f * vehicleAeroFriction_ * 0.25f * bodySpeed * bodySpeed;
    // Simulate car aerodynamics friction
    body_->ApplyForce(aeroForceMagnitude * currBodyVelDir, body_->GetWorldCenter(), true);
}

void Wheel::UpdateFrictionNotLocked(float dt) {
    b2Vec2 impulse = body_->GetMass() * -GetLateralVelocity();
    if (impulse.Length() > dt * maxTireFrictionForce_* 100.)
        impulse *= dt * maxTireFrictionForce_ * 100./ impulse.Length();

    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
    body_->ApplyAngularImpulse(0.5f * body_->GetInertia() * -body_->GetAngularVelocity(), true);

    b2Vec2 currForwardVel = GetForwardVelocity();
    b2Vec2 currBodyVelDir = body_->GetLinearVelocity();
    float bodySpeed = currBodyVelDir.Normalize();
    float currForwardSpeed = currForwardVel.Normalize();
    float aeroForceMagnitude = -0.1f * vehicleAeroFriction_ * 0.25f * bodySpeed * bodySpeed;
    float dragForceMagnitude = -(0.1f + 0.5 * frictionModifier_) * 0.2f * currForwardSpeed;
    // Simulate wheel drag force
    body_->ApplyForce(dragForceMagnitude * currForwardVel, body_->GetWorldCenter(), true);
    // Simulate car aerodynamics friction
    body_->ApplyForce(aeroForceMagnitude * currBodyVelDir, body_->GetWorldCenter(), true);
}

b2Vec2 Wheel::GetLateralVelocity() {
    b2Vec2 currentRightNormal = body_->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body_->GetLinearVelocity()) *
           currentRightNormal;
}

b2Vec2 Wheel::GetForwardVelocity() {
    b2Vec2 currentRightNormal = body_->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentRightNormal, body_->GetLinearVelocity()) *
           currentRightNormal;
}

void Wheel::Brake() {
    locked_ = true;
}

void Wheel::ReleaseBrake() {
    locked_ = false;
}

WheelPositionE Wheel::GetWheelType() {
    return this->positionFlag_;
}