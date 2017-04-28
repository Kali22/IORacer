#pragma once
//
// Created by pawel on 03.04.17.
//

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <CheckPointObserver.h>
#include <Tools/RectangleArea.h>
#include <Tools/RectangleParams.h>
#include <Tools/Area.h>

/**
 * Check point is specyfic area. When car reach area enabled checkpoint
 * notify observer about change and set its state to disable.
 */
class CheckPoint : public Entity {
public:
    CheckPoint(RectangleArea *area, const sf::Texture *texture);

    void Draw(sf::RenderWindow *window) const;

    virtual int GetEntityType() const;

    void SetEnable(bool value);

    bool IsEnabled() const;

    /**
     * Set observer who is notifed each time when enabled checkpoint is
     * reached by car.
     */
    void SetObserver(CheckPointObserver *observer);

    /**
     * Set enable to false and notify observer. Should be called by contact
     * listener when car reach checkpoint.
     */
    void BeginContact();

    void EndContact();

    sf::Vector2f GetPosition() const;

private:
    RectangleArea *area_;
    CheckPointObserver *observer_;
    bool enable_;
};

using CheckPointPtr = std::shared_ptr<CheckPoint>;

