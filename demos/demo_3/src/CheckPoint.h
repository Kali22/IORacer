#pragma once
//
// Created by pawel on 03.04.17.
//

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <Car.h>
#include <CheckPointObserver.h>

class CheckPoint : public Entity {
public:
    virtual int GetEntityType();

    void Enable();

    bool IsEnabled();

    void SetObserver(CheckPointObserver* observer);

    b2Vec2 GetPosition();
    b2Vec2 GetSize();
    void draw(sf::Window* window);
    CheckPoint(b2World* world, b2Vec2 pointA, b2Vec2 pointB);

    void BeginContact();

    void EndContact();

    void Draw(sf::RenderWindow* window);

    void DebugPrint();
private:
    void CreateSFMLRectangle(b2Vec2 position, b2Vec2 size);

    void CreateB2Rectangle(b2Vec2 position, b2Vec2 size);

    sf::Vector2f b2VectorToSFML(const b2Vec2& vec);

    sf::RectangleShape rectangleShape_;
    CheckPointObserver* observer_;
    b2Vec2 position_;
    b2Vec2 size_;
    b2Body* body_;
    b2World* world_;
    bool isActive_;
};

