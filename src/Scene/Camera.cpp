#include <Object.h>
#include "Camera.h"

Camera::Camera(RealVec center, float refHeigth, float screenFraction) :
        center_(center),
        trackedObject_(nullptr),
        referenceHeight_(refHeigth),
        screenFraction_(screenFraction) {
}

Camera::Camera(VehiclePtr tracked, float refHeigth, float screenFraction) :
        trackedObject_(tracked),
        center_(tracked->GetPosition()),
        referenceHeight_(refHeigth),
        screenFraction_(screenFraction) {
}

float Camera::GetReferenceHeight() const {
    return referenceHeight_;
}

float Camera::GetScreenFraction() const {
    return screenFraction_;
}

RealVec Camera::GetCenter() const {
    if (trackedObject_ == nullptr) {
        return center_;
    } else {
        return  trackedObject_->GetPosition();
    }
}

void Camera::ChangeView(float ref, float frac) {
    referenceHeight_ = ref;
    screenFraction_ = frac;
}

VehiclePtr Camera::GetTrackedObject() const{
    return trackedObject_;
}

