/**
 *  @defgroup vehicle Vehicle
 *  Vehicle model control
 */

/**
 *  @file
 *  @ingroup vehicle
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#pragma once

#include <vector>
#include <Box2D.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Tire.h>
#include <Map.h>
#include <Entity.h>

class Vehicle : public Entity {
public:
    Vehicle(CarParametersPtr params, float scale);

    ~Vehicle();

    void Initialize(b2World *world, int x, int y);

    void Update(int state, Map &map);

    void Reset(int x, int y);

    void Render(sf::RenderWindow &window);

    const sf::Vector2f &GetPosition() const;

    sf::Vector2f GetBoxPosition() const;

    CarParametersPtr GetCarParameters() const;

    float GetAngle() const;

    float GetBoxAngle() const;

    float GetSpeed() const;

    float GetTireModifier(int i, Map &map) const;

    void PrintPos() const;

    virtual int GetEntityType() const;

private:
    float scale_;
    b2Body *body;
    std::vector<TirePtr> tires;
    b2RevoluteJoint *fl_joint, *fr_joint; // Front joints
    b2RevoluteJoint *bl_joint, *br_joint; // Back joints

    sf::Texture texture_chassis;
    sf::Sprite sprite_chassis;

    CarParametersPtr carParameters_;

    void UpdateFriction(Map &map);

    void UpdateDrive(int controlState, Map &map);

    void UpdateTurn(int controlState);

    void
    CreateTire(b2World *world, b2RevoluteJoint **joint, b2RevoluteJointDef &jointDef, float arg1, float arg2,
                   float x, float y, int positionFlags);
};

using VehiclePtr = std::shared_ptr<Vehicle>;