//
// Created by pawel on 03.04.17.
//

#include <iostream>

#include <Box2D.h>
#include <CheckPoint.h>
#include <Car.h>
#include <SFML/Graphics/View.hpp>
#include <Entity.h>


sf::Vector2f CheckPoint::b2VectorToSFML(const b2Vec2 &vec) {
    return sf::Vector2f(vec.x * 30, vec.y * 30);
}

int CheckPoint::GetEntityType() {
    return CHECK_POINT;
}

b2Vec2 CheckPoint::GetPosition() {
    return position_;
}

b2Vec2 CheckPoint::GetSize() {
    return size_;
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

void CheckPoint::DebugPrint() {
    std::cout << "CheckPoint ";
    std::cout << body_->GetPosition().x << " "
              << body_->GetPosition().y << std::endl;
}

void CheckPoint::CreateB2Rectangle(b2Vec2 position, b2Vec2 size) {
    b2BodyDef bodyDef;
    bodyDef.position = position;
    body_ = world_->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2);

    fixtureDef.shape = &polygonShape;
    fixtureDef.isSensor = true;

    b2Fixture *checkPointFixture = body_->CreateFixture(&fixtureDef);
    body_->SetUserData(this);
}

void CheckPoint::CreateSFMLRectangle(b2Vec2 position, b2Vec2 size) {
    rectangleShape_ = sf::RectangleShape(b2VectorToSFML(size));
    sf::Vector2f convertedPos = b2VectorToSFML(position);
    convertedPos.x -= size.x * 30 / 2;
    convertedPos.y -= size.y * 30 / 2;

    rectangleShape_.setPosition(convertedPos);
}

CheckPoint::CheckPoint(b2World *world, b2Vec2 position, b2Vec2 size)
        : world_(world), position_(position), size_(size), isActive_(false) {
    CreateB2Rectangle(position, size);
    CreateSFMLRectangle(position, size);
}

void CheckPoint::Draw(sf::RenderWindow *window) {
    if (isActive_) {
        window->draw(rectangleShape_);
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

