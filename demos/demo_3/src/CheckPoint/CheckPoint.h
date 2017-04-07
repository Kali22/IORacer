#pragma once

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <Area.h>
#include <Car.h>
#include <CheckPointObserver.h>
#include <RectangleArea.h>
#include <RectangleParams.h>

class CheckPoint : public Entity {
public:
    virtual int GetEntityType();

    void Enable();

    bool IsEnabled();

    void SetObserver(CheckPointObserver* observer);

    CheckPoint(Area* area);

    ~CheckPoint();

    void BeginContact();

    void EndContact();

    void Draw(sf::RenderWindow* window);
private:
    Area* area_;
    CheckPointObserver* observer_;
    bool isActive_;
};

