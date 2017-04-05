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
#include <Map.h>


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

    CarParameters &carParameters;

    void updateFriction(Map &map);
    void updateDrive(int controlState, Map &map);
    void updateTurn(int controlState);
public:
    Vehicle(CarParameters &params);
    ~Vehicle();

    void Render(sf::RenderWindow &window);

    const sf::Vector2f &GetPosition() const;
    float GetAngle();
    float GetBoxAngle();
    float GetSpeed();
    sf::Vector2f GetBoxPosition() const;

    void Update(int state, Map &map);
    void Initialize(b2World *world, int x, int y);
};


#endif //Vehicle
