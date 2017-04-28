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

    void Initialize(b2World *world, int posX, int posY);

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
    b2Body *body_;
    std::vector<TirePtr> tires_;
    b2RevoluteJoint *fl_joint_, *fr_joint_; // Front joints
    b2RevoluteJoint *bl_joint_, *br_joint_; // Back joints

    sf::Texture texture_chassis_;
    sf::Sprite sprite_chassis_;

    CarParametersPtr carParameters_;

    void UpdateFriction(Map &map);

    void UpdateDrive(int controlState, Map &map);

    void UpdateTurn(int controlState);

    void CreateTire(b2World *world, b2RevoluteJoint **joint, b2RevoluteJointDef &jointDef,
                    float bodyOffSetX, float bodyOffSetY,
                    float posX, float posY, TirePositionE positionFlags);

    void CreateTires(b2World *world, int posX, int posY);

    void InitializeBody(b2World *world, int posX, int posY, float angle);

    void InitializeBodyFixture();

    float GetDesiredAngle(int controlState);
};

using VehiclePtr = std::shared_ptr<Vehicle>;
