//
// Created by pawel on 03.04.17.
//

#include <iostream>

#include <Box2D.h>
#include <CheckPoint.h>
#include <Car.h>
#include <SFML/Graphics/View.hpp>
#include <Entity.h>

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

CheckPoint::CheckPoint(b2World *world,
                       const b2Vec2& position,
                       const b2Vec2& size,
                       float angle)
        : world_(world), rectangleArea_(world, position, size, angle, this) {
}

void CheckPoint::Draw(sf::RenderWindow *window) {
    if (isActive_) {
        rectangleArea_.Draw(window);
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
    std::cout << "End contact\n";
}

CheckPoint::~CheckPoint() {}

