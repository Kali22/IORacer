#include <CheckPoint.h>

CheckPoint::CheckPoint(int id, b2Body *body, VisualObjectPtr visualObject) :
        Object(body, visualObject, OBJECT_TYPE_CHECK_POINT), playerId_(id) {
    body_->SetUserData(this);
}

void CheckPoint::SetObserver(CheckPointObserver *observer) {
    observer_ = observer;
}

void CheckPoint::SetEnabled(bool value) {
    enabled_ = value;
}

bool CheckPoint::IsEnabled() const {
    return enabled_;
}

void CheckPoint::BeginContact() {
    if (enabled_) {
        enabled_ = false;
        if (observer_ != nullptr) {
            observer_->NotifyCheckPointReached();
        }
    }
}

void CheckPoint::Draw(RenderWindowPtr window) {
    if (IsEnabled()) {
        Object::Draw(window);
    }
}

void CheckPoint::EndContact() {}

int CheckPoint::GetId() const {
    return playerId_;
}
