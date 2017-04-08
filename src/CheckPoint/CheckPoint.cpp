#include <iostream>

#include <Box2D.h>
#include <CheckPoint.h>
#include <Vehicle.h>
#include <SFML/Graphics/View.hpp>
#include <Entity.h>
#include <Area.h>

CheckPoint::CheckPoint(Area* area) : area_(area) {
    area_->SetCollisionUserData(this);
}

CheckPoint::~CheckPoint() {}

int CheckPoint::GetEntityType() const {
    return CHECK_POINT;
}

void CheckPoint::SetObserver(CheckPointObserver* observer) {
    observer_ = observer;
}

void CheckPoint::Enable() {
    isActive_ = true;
}

bool CheckPoint::IsEnabled() const {
    return isActive_;
}

void CheckPoint::Draw(sf::RenderWindow *window) const {
    if (isActive_) {
        area_->Draw(window);
    }
}

void CheckPoint::BeginContact() {
    if (isActive_) {
        isActive_ = false;
        if (observer_ != nullptr) {
            observer_->NotifyCheckPointReached();
        }
    }
}

void CheckPoint::EndContact() {
}


