#pragma once

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>
#include <Entity.h>
#include <RectangleParams.h>
#include <Area.h>

class RectangleArea : public Area {
public:
    RectangleArea(b2World* world, const struct RectangleParams& params);

    ~RectangleArea();

    void Draw(sf::RenderWindow* window) const;

    void SetCollisionUserData(Entity* entity);
private:
    void CreateSFMLRectangle(const sf::Vector2f& position,
                             const sf::Vector2f& size,
                             float angle);

    void CreateB2Rectangle(const b2Vec2& position, const b2Vec2& size,
                           float angle);
    sf::RectangleShape rectangleShape_;
    b2Body* body_;
    b2World* world_;
};

