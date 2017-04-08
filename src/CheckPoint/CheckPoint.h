#pragma once
//
// Created by pawel on 03.04.17.
//

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <CheckPointObserver.h>
#include <RectangleArea.h>
#include <RectangleParams.h>
#include <Area.h>

class CheckPoint : public Entity {
public:
    CheckPoint(Area *area);

    ~CheckPoint();

    void Draw(sf::RenderWindow *window) const;

    virtual int GetEntityType() const;

    void SetEnable(bool value);

    bool IsEnabled() const;

    void SetObserver(CheckPointObserver *observer);

    void BeginContact();

    void EndContact();

private:
    Area *area_;
    CheckPointObserver *observer_;
    bool enable_;
};

using CheckPointPtr = std::shared_ptr<CheckPoint>;

