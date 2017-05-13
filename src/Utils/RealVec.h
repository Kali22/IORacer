#pragma once


#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

class RealVec : public sf::Vector2f {
public:
    RealVec();

    RealVec(float scalePixInMeters);

    RealVec(float x, float y);

    RealVec(const b2Vec2& vec);

    RealVec(const sf::Vector2f &vec);

    RealVec(const sf::Vector2f &vec, float scalePixInMeters);

    float GetScale() const;

    void SetScale(float scalePixInMeters);

    sf::Vector2f GetScaledVector() const;

    RealVec &operator=(const RealVec &vec);

    RealVec &operator=(const sf::Vector2f &vec);

private:
    float scale_;
};

