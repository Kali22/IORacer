/**
 * @addtogroup tire
 * @ingroup vehicle
 */

/**
 *  @file
 *  @ingroup tire
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#pragma once

#include <Dynamics/b2Body.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "CarParams.h"
#include <Tools/Entity.h>

class Tire : public Entity {
public:
    virtual int GetEntityType() const;

    sf::Texture tireTexture;
    sf::Sprite tireSprite;

    b2Body *body;

    Tire(b2World *world, float scale, float x, float y, CarParametersPtr carParameters, int positionFlags);

    ~Tire();

    void Reset(float x, float y);

    b2Vec2 GetLateralVelocity();

    b2Vec2 GetForwardVelocity();


    void UpdateFriction(float mod);

    void Render(sf::RenderWindow &window);

    void UpdateDrive(int state, float mod);

    /**
     * Returns tire position flags.
     * @return position flags
     */
    int GetTirePositionFlags() const;
private:
    /// Car parameters structure
    CarParametersPtr carParameters_;
    /// Tire position in car
    int tirePositionFlags_;
    /// Is wheel is locked?
    bool locked_;

    /// Max possible friction force
    float maxTireFrictionForce_; // = frictionBase * frictionMod * loadForce
};


using TirePtr = std::shared_ptr<Tire>;
