/**
 *  @file
 *  @ingroup vehicle
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <iostream>
#include <cassert>
#include "VehicleObject.h"
#include <TireControlE.h>
#include <MathUtil.h>

VehicleObject::VehicleObject(b2World *world, VisualObjectPtr visualObject,
                             std::vector<TirePtr> tires)
        : Object(InitializeBody(world, visualObject->GetSize()), visualObject) {
    assert(tires.size() == 4);
    tires_ = tires;
    body_->SetUserData(this);
    InitializeTires(world);
}

VehicleObject::~VehicleObject() {
    body_->GetWorld()->DestroyJoint(fl_joint_);
    body_->GetWorld()->DestroyJoint(fr_joint_);
    body_->GetWorld()->DestroyJoint(bl_joint_);
    body_->GetWorld()->DestroyJoint(br_joint_);
    body_->GetWorld()->DestroyBody(body_);
}

void VehicleObject::Draw(RenderWindowPtr window) const {
    Object::Draw(window);
    for (auto &tire : tires_) {
        tire->Draw(window);
    }
}

void VehicleObject::Update(int state, MapPtr map, CarParametersPtr params) {
    UpdateFriction(map);
    UpdateDrive(state, map, params);
    UpdateTurn(state, params);
}

void VehicleObject::InitializeFixture(b2Body* body, const RealVec& size) {
    b2PolygonShape Shape;
    Shape.SetAsBox(size.x / 2, size.y / 2);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 4.f;
    FixtureDef.friction = 1.7f;
    FixtureDef.restitution = 0.5;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);
}

// TODO set position and angle
b2Body *VehicleObject::InitializeBody(b2World *world, const RealVec& realSize) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body *body = world->CreateBody(&bodyDef);
    body->SetAngularVelocity(0);
    body->SetLinearVelocity(b2Vec2(0, 0));
    InitializeFixture(body, realSize);
    return body;
}

void VehicleObject::InitializeTires(b2World *world) {
    // Create TIRES
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body_;
    jointDef.referenceAngle = 0;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;        //with both these at zero...
    jointDef.upperAngle = 0;        //...the joint will not move
    jointDef.localAnchorB.SetZero();//joint anchor in tire is always center

    tires_[0]->InitializeTire(world, &fl_joint_, jointDef, -17.f,
                              18.f,
                              LEFT_FRONT_TIRE);
    tires_[1]->InitializeTire(world, &fr_joint_, jointDef, 17.f, 18.f,
                              RIGHT_FRONT_TIRE);
    tires_[2]->InitializeTire(world, &bl_joint_, jointDef, 17.f,
                              -17.f,
                              RIGHT_REAR_TIRE);
    tires_[3]->InitializeTire(world, &br_joint_, jointDef, -17.f,
                              -17.f,
                              LEFT_REAR_TIRE);
}

void VehicleObject::Reset(int x, int y) { // TODO realvec
    body_->SetAngularVelocity(0);
    body_->SetLinearVelocity(b2Vec2(0, 0));
    body_->SetTransform(b2Vec2(x, y), b2_pi / 2);
    fl_joint_->SetLimits(0, 0);
    fr_joint_->SetLimits(0, 0);
    for (auto tire : tires_) {
        tire->Reset(x, y);
    }
}

void VehicleObject::UpdateFriction(MapPtr map) {
    for (auto &tire : tires_) {
        float modifier = map->GetFrictionModifier(tire->GetPosition());
        tire->UpdateFriction(modifier);
    }
}

void VehicleObject::UpdateDrive(int controlState, MapPtr map, CarParametersPtr
params) {
    for (auto &tire : tires_) {
        float modifier = map->GetFrictionModifier(tire->GetPosition());

        if (tire->IsFront())
            tire->UpdateDrive(controlState & ~UP, modifier, params);
        else
            tire->UpdateDrive(controlState & ~(BRAKE), modifier, params);
    }
}

void VehicleObject::UpdateTurn(int controlState, CarParametersPtr params) {
    float turnSpeedPerSec = MathUtil::DegreeToRadian(
            params->steeringSpeed);
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = GetDesiredAngle(controlState, params);

    desiredAngle *= (1.f - 0.8f * abs((int) GetSpeed()) /
                           params->maxForwardSpeed);
    float angleNow = fl_joint_->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;

    fl_joint_->SetLimits(newAngle, newAngle);
    fr_joint_->SetLimits(newAngle, newAngle);
}

float VehicleObject::GetDesiredAngle(int controlState, CarParametersPtr
params) {
    float desiredAngle = 0;
    float maxSteeringAngleRadians = MathUtil::DegreeToRadian(
            params->maxSteeringAngle);
    switch (controlState & (LEFT | RIGHT)) {
        case LEFT:
            desiredAngle = -maxSteeringAngleRadians;
            break;
        case RIGHT:
            desiredAngle = maxSteeringAngleRadians;
            break;
        default:;//nothing
    }
    return desiredAngle;
}

float VehicleObject::GetSpeed() const {
    b2Vec2 vel = body_->GetLinearVelocity();
    return (float) sqrt(b2Dot(vel, vel));
}

float VehicleObject::GetTireModifier(int i, MapPtr map) const {
    return map->GetFrictionModifier(tires_[i]->GetPosition());
}

void VehicleObject::PrintPos() const {
    std::cout << "Car " << body_->GetPosition().x << " "
              << body_->GetPosition().y << std::endl;
}

int VehicleObject::GetObjectType() const {
    return CAR;
}

float VehicleObject::GetAngle() const {
   return MathUtil::RadianToDegree(body_->GetAngle());
}

float VehicleObject::GetBoxAngle() const {
    return body_->GetAngle();
}
