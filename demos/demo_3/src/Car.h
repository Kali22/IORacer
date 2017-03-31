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
    LEFT = 0x1,
    RIGHT = 0x2,
    UP = 0x4,
    DOWN = 0x8
};

class Car {
private:
    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();
    void updateFriction();
    void updateDrive(int controlState);
    void updateTurn(int controlState);

    b2Body *body;
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;

public:
    Car(b2World *world, int x, int y);

    ~Car();

    void Update(int state);
    void Draw(sf::RenderWindow &window, sf::Texture texture);
    void setCharacteristics(float maxForwardSpeed_, float maxBackwardSpeed_, float maxDriveForce_);
};


#endif //Car
