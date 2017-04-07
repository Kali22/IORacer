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
    CheckPoint(Area* area);
    ~CheckPoint();

    void Draw(sf::RenderWindow* window) const;
    virtual int GetEntityType() const;

    void Enable();
    bool IsEnabled() const;

    void SetObserver(CheckPointObserver* observer);

    void BeginContact();
    void EndContact();
private:
    Area* area_;
    CheckPointObserver* observer_;
    bool isActive_;
};

