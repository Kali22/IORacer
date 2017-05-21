#pragma once

#include <ObjectTypes.h>
#include <Wheel.h>
#include <bits/stdc++.h>
#include <vector>
#include "VehicleSetup.h"

class Vehicle : public Object {
public:
    Vehicle(b2Body *body, VisualObjectPtr chassis, std::vector<WheelPtr> &&wheels, const VehicleSetupT &setup,
                MapPtr map);

    ~Vehicle();

    void Accelerate(bool state);

    void Reverse(bool state);

    void TurnLeft(bool state);

    void TurnRight(bool state);

    void Brake(bool state);

    void Update(float dt);

    void Draw(RenderWindowPtr window);

    void Rescale(float scale);

    void Reset(float x, float y, float rot);

    void ChangeVehicleSetup(const VehicleSetupT setup);

    void PrintDiagnostic();

private:
    void InitializeWheels();

    void UpdateFriction(float dt);

    void UpdateDrive(float dt);

    void UpdateTurn(float dt);

    void UpdateModifiers();

    /* Compounds */
    std::vector<WheelPtr> wheels_;
    b2RevoluteJoint *fl_joint_, *fr_joint_; // Front joints
    b2RevoluteJoint *bl_joint_, *br_joint_; // Back joints

    MapPtr map_;

    /* Car state */
    int controllerState_;
    float enginePowerNow_;
    float steeringAngleNow_;

    /* Car params */
    VehicleSetupT vehicleSetup_;

    float GetDesiredAngle();
};
using VehiclePtr = std::shared_ptr<Vehicle>;