/**
 * @defgroup car
 * Car object.
 */

/**
 *  @file
 *  @ingroup car
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#ifndef _Car_H_
#define _Car_H_

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

enum car_control_e {
    LEFT    =   0x01,
    RIGHT   =   0x02,
    UP      =   0x04,
    DOWN    =   0x08,
    BRAKE   =   0x10
};

class Car {
private:
    sf::Texture car_texture;
    sf::Sprite car_sprite;

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
    void updateFriction(float modifier);
    void updateDrive(int controlState);
    void updateTurn(int controlState);

    b2Body *body;
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;

public:
    Car();
    ~Car();
    void Initialize(b2World *world, int x, int y);

    void Update(int state, float modifier);
    const sf::Drawable &GetSprite() ;
    void setCharacteristics(float maxForwardSpeed_, float maxBackwardSpeed_, float maxDriveForce_);

    const sf::Vector2f &GetPosition() const;
    float GetRotation();
    float GetSpeed();
};


#endif //Car
