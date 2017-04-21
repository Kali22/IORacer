//
// Created by jacek on 20.04.17.
//

#include "Container.h"

Container::Container(sf::FloatRect rect) {
    rect_.setOrigin(0, 0);
    rect_.setSize(sf::Vector2f(rect.width, rect.height));
    rect_.setPosition(rect.left, rect.top);
    rect_.setFillColor(sf::Color(30, 30, 30, 100));
    rect_.setOutlineThickness(2.f);
    rect_.setOutlineColor(sf::Color(230, 230, 0, 100));
    visible_ = true;
}

void Container::Draw(sf::RenderWindow *window) const {
    if (visible_) {
        if (frame_)
            window->draw(rect_);
        auto absolutePosition = rect_.getPosition();
        for (auto el : list_) {
            if (el != nullptr) {
                el->Move(absolutePosition);
                el->Draw(window);
                el->Move(-absolutePosition);
            }
        }
    }
}

void Container::SetPosition(const sf::Vector2f &pos) {
    rect_.setPosition(pos);
}

void Container::SetPosition(float x, float y) {
    rect_.setPosition(x, y);
}

void Container::Move(const sf::Vector2f &dr) {
    rect_.move(dr);
}

void Container::Move(float dx, float dy) {
    rect_.move(dx, dy);
}

Container::~Container() {

}

void Container::FrameOn() {
    frame_ = true;
}

void Container::FrameOff() {
    frame_ = false;
}

/// Create with std::make_shared<CheckPoint>(new Object);
void Container::AddMovable(MovablePtr movablePtr) {
    list_.push_back(movablePtr);
}

void Container::Show() {
    visible_ = true;
}

void Container::Hide() {
    visible_ = false;
}

void Container::Update() {
    for (auto el : updatableList_) {
        el->Update();
    }
}

void Container::AddUpdatable(UpdatablePtr updatablePtr) {
    updatableList_.push_back(updatablePtr);
}
