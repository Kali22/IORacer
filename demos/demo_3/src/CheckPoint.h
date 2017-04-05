#pragma once
//
// Created by pawel on 03.04.17.
//

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <Car.h>
#include <CheckPointObserver.h>
#include <RectangleArea.h>

class CheckPoint : public Entity {
public:
    virtual int GetEntityType();

    void Enable();

    bool IsEnabled();

    void SetObserver(CheckPointObserver* observer);

    void Draw(sf::Window* window);

    CheckPoint(b2World* world, const b2Vec2& position, const b2Vec2& size,
               float angle);

    ~CheckPoint();

    void BeginContact();

    void EndContact();

    void Draw(sf::RenderWindow* window);
private:
    RectangleArea rectangleArea_;
    CheckPointObserver* observer_;
    b2World* world_;
    bool isActive_;
};

