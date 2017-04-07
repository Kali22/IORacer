#include <iostream>

#include <Box2D.h>
#include <CheckPoint.h>
#include <Car.h>
#include <SFML/Graphics/View.hpp>
#include <Entity.h>
#include <Area.h>

int CheckPoint::GetEntityType() {
    return CHECK_POINT;
}

void CheckPoint::SetObserver(CheckPointObserver* observer) {
    observer_ = observer;
}

void CheckPoint::Enable() {
    isActive_ = true;
}

bool CheckPoint::IsEnabled() {
    return isActive_;
}

CheckPoint::CheckPoint(Area* area) : area_(area) {
    area_->SetCollisionUserData(this);
}

void CheckPoint::Draw(sf::RenderWindow *window) {
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
    std::cout << "Begin contact\n";
}

void CheckPoint::EndContact() {
}

CheckPoint::~CheckPoint() {}

