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
#include "Tire.h"
#include <Map.h>
#include <Object.h>
#include <VehicleObject.h>

class VehicleObject : public Object {
public:
    VehicleObject(b2World *world,  VisualObjectPtr visualObject,
                  std::vector<TirePtr> tires);

    ~VehicleObject();

    void Update(int state, MapPtr map, CarParametersPtr params);

    void Reset(int x, int y);

    virtual void Draw(RenderWindowPtr window) const;

    float GetSpeed() const;

    float GetTireModifier(int i, MapPtr map) const;

    void PrintPos() const;

    virtual int GetObjectType() const;

    float GetAngle() const;

    float GetBoxAngle() const;

    // TODO set position
private:
    static b2Body* InitializeBody(b2World *world, const RealVec& size);

    static void InitializeFixture(b2Body* body, const RealVec& realSize);

    void UpdateFriction(MapPtr map);

    void UpdateDrive(int controlState, MapPtr map, CarParametersPtr params);

    void UpdateTurn(int controlState, CarParametersPtr params);

    void InitializeTires(b2World *world);

    float GetDesiredAngle(int controlState, CarParametersPtr params);

    std::vector<TirePtr> tires_;
    b2RevoluteJoint *fl_joint_, *fr_joint_; // Front joints
    b2RevoluteJoint *bl_joint_, *br_joint_; // Back joints
};


using VehicleObjectPtr = std::shared_ptr<VehicleObject>;
