#pragma once

#include <bits/stdc++.h>
#include <Trackable.h>
#include <RealVec.h>

class Camera {
public:
    Camera(RealVec center, float refHeight, float screenFraction);
    Camera(TrackablePtr tracked, float refHeight, float screenFraction);

    float GetReferenceHeight() const;

    float GetScreenFraction() const;

    RealVec GetCenter() const;

private:
    float referenceHeight_;
    float screenFraction_;
    RealVec center_;
    TrackablePtr trackedObject_;
};

using CameraPtr = std::shared_ptr<Camera>;