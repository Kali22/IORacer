#include <GameObjects/CheckPoint/CheckPoint.h>

CheckPoint::CheckPoint(int id, b2Body *body, VisualObjectPtr visualObject)
        : Object(body, visualObject, OBJECT_TYPE_CHECK_POINT), playerId_(id) {
    body_->SetUserData(this);
}

void CheckPoint::SetObserver(CheckPointObserver *observer) {
    observer_ = observer;
}

void CheckPoint::SetEnable(bool value) {
    enable_ = value;
}

bool CheckPoint::IsEnable() const {
    return enable_;
}

void CheckPoint::BeginContact() {
    if (enable_) {
        enable_ = false;
        if (observer_ != nullptr) {
            observer_->NotifyCheckPointReached();
        }
    }
}

void CheckPoint::Draw(RenderWindowPtr window) {
    if (IsEnable()) {
        Object::Draw(window);
    }
}

void CheckPoint::EndContact() {}

int CheckPoint::GetId() const {
    return playerId_;
}

