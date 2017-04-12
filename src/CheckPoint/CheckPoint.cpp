#include <CheckPoint.h>

CheckPoint::CheckPoint(Area *area) : area_(area) {
    area_->SetCollisionUserData(this);
}

CheckPoint::~CheckPoint() {}

int CheckPoint::GetEntityType() const {
    return CHECK_POINT;
}

void CheckPoint::SetObserver(CheckPointObserver *observer) {
    observer_ = observer;
}

void CheckPoint::SetEnable(bool value) {
    enable_ = value;
}

bool CheckPoint::IsEnabled() const {
    return enable_;
}

void CheckPoint::Draw(sf::RenderWindow *window) const {
    area_->Draw(window);
}

void CheckPoint::BeginContact() {
    if (enable_) {
        enable_ = false;
        if (observer_ != nullptr) {
            observer_->NotifyCheckPointReached();
        }
    }
}

void CheckPoint::EndContact() {}

sf::Vector2f CheckPoint::GetPosition() const {
    return area_->GetPosition();
}


