#pragma once


#include <bits/stdc++.h>
#include <Dynamics/Joints/b2RevoluteJoint.h>
#include <Object.h>
#include "WheelPositionE.h"

class Wheel : public Object {
public:
    Wheel(b2Body *body, VisualObjectPtr wheel);

    ~Wheel();

    void InitializeWheel(b2RevoluteJoint **jointPtr, b2RevoluteJointDef &jointDef, float bodyOffSetX, float bodyOffSetY,
                         WheelPositionE positionFlag);

    void UpdateModifiers(float groundMod, float reactF, float vehicleAeroFriction);

    void UpdateFriction(float dt);

    void UpdateDrive(float torque,  float dt);

    void Brake();

    void ReleaseBrake();

    void Reset(float x, float y, float angle);

    bool IsFront() const;

    bool IsLeft() const;

    WheelPositionE GetWheelType();

private:
    b2Vec2 GetLateralVelocity();

    b2Vec2 GetForwardVelocity();

    void UpdateFrictionLocked(float dt);

    void UpdateFrictionNotLocked(float dt);


    WheelPositionE positionFlag_;
    bool locked_;
    float frictionModifier_;
    float maxTireFrictionForce_;
    float vehicleAeroFriction_;
    const float wheelRadius_ = 0.2;

};

