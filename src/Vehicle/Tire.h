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
#include <Vehicle/CarParams.h>
#include <Tools/Entity.h>
#include <Vehicle/TirePositionE.h>

/**
 * Tire class.
 * Vehicle component.
 * Responsible for interaction with ground.
 */
class Tire : public Entity {
public:
    virtual int GetEntityType() const;

    sf::Texture tireTexture;
    sf::Sprite tireSprite;

    b2Body *body;

    Tire(b2World *world, float scale, float x, float y, CarParametersPtr carParameters, TirePositionE positionFlags);

    ~Tire();

    void Reset(float x, float y);

    b2Vec2 GetLateralVelocity();

    b2Vec2 GetForwardVelocity();

    void UpdateFriction(float mod);

    void Render(sf::RenderWindow &window);

    void UpdateDrive(int state, float mod);

    bool IsLeft() const;

    bool IsFront() const;

private:
    /// Car parameters structure
    CarParametersPtr carParameters_;
    /// Tire position in car
    TirePositionE tirePosition_;
    /// Is wheel locked?
    bool locked_;

    /// Max possible friction force.
    /// = frictionBase * frictionMod * loadForce
    float maxTireFrictionForce_;

    void UpdateFrictionLocked(float mod);

    void UpdateFrictionNotLocked(float mod);

    void InitializeBody(b2World *world, float scale, float x, float y);

    float GetDesiredSpeed(int state);

    float GetNecessaryForce(float currentSpeed, float desiredSpeed);
};

using TirePtr = std::shared_ptr<Tire>;
