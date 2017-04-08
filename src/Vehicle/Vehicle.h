/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#pragma once

#include <Box2D.h>
#include <vector>
#include <Tire.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Map.h>
#include <Entity.h>

class Vehicle : public Entity {
public:
    Vehicle(CarParameters &params, float scale);

    ~Vehicle();

    void PrintPos();

    virtual int GetEntityType() const;

    void Render(sf::RenderWindow &window);

    const sf::Vector2f &GetPosition() const;

    float GetAngle();

    float GetBoxAngle();

    float GetSpeed();

    float GetTireModifier(int i, Map &map);

    sf::Vector2f GetBoxPosition() const;

    void Update(int state, Map &map);

    void Initialize(b2World *world, int x, int y);

    CarParameters *getCarParameters();

private:
    float scale_;
    b2Body *body;
    std::vector<TirePtr> tires;
    b2RevoluteJoint *fl_joint, *fr_joint; // Front joints
    b2RevoluteJoint *bl_joint, *br_joint; // Back joints

    sf::Texture texture_chassis;
    sf::Sprite sprite_chassis;

    CarParameters &carParameters;

    void updateFriction(Map &map);

    void updateDrive(int controlState, Map &map);

    void updateTurn(int controlState);

    void createTire(b2World *world, b2RevoluteJoint **fl_joint, b2RevoluteJointDef &jointDef, float arg1, float arg2);
};

using VehiclePtr = std::shared_ptr<Vehicle>;