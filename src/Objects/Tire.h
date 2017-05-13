/**
 * @file
 * @addtogroup tire
 * @ingroup vehicle
 * @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 * @date 4/1/17
 */

#pragma once

#include <Dynamics/b2Body.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <CarParams.h>
#include <TirePositionE.h>
#include <Object.h>
#include <VisualObject.h>

/**
 * Tire class.
 * VehicleObject component.
 * Responsible for interaction with ground.
 */
class Tire : public Object {
public:
    virtual int GetObjectType() const;

    Tire(b2World *world, VisualObjectPtr visualObject);

    ~Tire();

    void Reset(float x, float y);

    b2Vec2 GetLateralVelocity();

    b2Vec2 GetForwardVelocity();

    void UpdateFriction(float mod);

    void UpdateDrive(int state, float mod, CarParametersPtr params);

    void InitializeTire(b2World *world, b2RevoluteJoint **jointPtr,
                        b2RevoluteJointDef &jointDef,
                        float bodyOffSetX, float bodyOffSetY,
                        TirePositionE positionFlag);

    bool IsLeft() const;

    bool IsFront() const;

private:
    void UpdateFrictionLocked(float mod);

    void UpdateFrictionNotLocked(float mod);

    static b2Body *InitializeBody(b2World *world, const RealVec& size);

    float GetDesiredSpeed(int state, CarParametersPtr params);

    float GetForce(float currentSpeed, float desiredSpeed, CarParametersPtr
    params);

    // Is wheel locked?
    bool locked_;
    // Max possible friction force.
    // = frictionBase * frictionMod * loadForce
    float maxTireFrictionForce_;
    // Tire position in car.
    TirePositionE tirePosition_;
};

using TirePtr = std::shared_ptr<Tire>;
