#pragma once


#include <bits/stdc++.h>
#include <Trackable.h>
#include <Vehicle.h>
#include <RealVec.h>

class Camera {
public:
    Camera(RealVec center, float refHeight, float screenFraction);

    Camera(VehiclePtr tracked, float refHeight, float screenFraction);

    float GetReferenceHeight() const;

    float GetScreenFraction() const;

    RealVec GetCenter() const;

    VehiclePtr GetTrackedObject() const;

    void ChangeView(float ref, float frac);

private:
    float referenceHeight_;
    float screenFraction_;
    RealVec center_;
    VehiclePtr trackedObject_;
};

using CameraPtr = std::shared_ptr<Camera>;
