#pragma once

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>
#include <Entity.h>
#include <RectangleParams.h>

class RectangleArea {
public:
    RectangleArea(b2World* world, const struct RectangleParams& params, Entity*
    entity);

    ~RectangleArea();

    void Draw(sf::RenderWindow* window);
private:
    sf::Vector2f b2VectorToSFML(const b2Vec2& vec);

    void CreateSFMLRectangle(const sf::Vector2f& position,
                             const sf::Vector2f& size,
                             float angle);

    void CreateB2Rectangle(const b2Vec2& position, const b2Vec2& size,
                           float angle, Entity* entity);
    sf::RectangleShape rectangleShape_;
    b2Body* body_;
    b2World* world_;
};


