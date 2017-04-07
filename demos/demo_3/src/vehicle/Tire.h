/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#ifndef _Tire_H_
#define _Tire_H_


#include <Dynamics/b2Body.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "CarParams.h"
#include <Entity.h>

class Tire : public Entity {
public:
    virtual int GetEntityType() const;

    sf::Texture tireTexture;
    sf::Sprite tireSprite;

    b2Body *body;
    float maxLateralImpulse;

    Tire(b2World *world);
    ~Tire();

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
    void updateFriction(float mod, CarParameters &params);


    void Render(sf::RenderWindow &window);
    void UpdateDrive(int state, float mod, CarParameters &params);
};


#endif //Tire
