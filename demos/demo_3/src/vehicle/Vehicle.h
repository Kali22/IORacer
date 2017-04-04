/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#ifndef _Vehicle_H_
#define _Vehicle_H_


#include <Box2D.h>
#include <vector>
#include <Tire.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
//
enum car_control_e {
    LEFT    =   0x01,
    RIGHT   =   0x02,
    UP      =   0x04,
    DOWN    =   0x08,
    BRAKE   =   0x10
};

class Vehicle {
private:
    b2Body *body;
    std::vector<Tire*> tires;
    b2RevoluteJoint *fl_joint, *fr_joint; // Front joints
    b2RevoluteJoint *bl_joint, *br_joint; // Back joints

    sf::Texture texture_chassis;
    sf::Sprite sprite_chassis;

    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
    float angle;


    void updateFriction(float modifier);
    void updateDrive(int controlState);
    void updateTurn(int controlState);
public:
    Vehicle();
    ~Vehicle();

    void Render(sf::RenderWindow &window);

    const sf::Vector2f &GetPosition() const;
    void setCharacteristics(float maxForwardSpeed_, float maxBackwardSpeed_, float maxDriveForce_);
    void Update(int state, float modifier);
    void Initialize(b2World *world, int x, int y);
};


#endif //Vehicle
