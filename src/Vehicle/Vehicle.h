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
#include <Object.h>
#include <VehicleObject.h>

class Vehicle : public Drawable {
public:
    Vehicle(CarParametersPtr params, VehicleObjectPtr vehicleObject);

    void Update(int state, MapPtr map);

    void Reset(int x, int y);

    RealVec GetPosition() const;

    void Draw(RenderWindowPtr window) const;

    CarParametersPtr GetCarParameters() const;

    float GetAngle() const;

    float GetBoxAngle() const;

    float GetSpeed() const;

    void PrintPos() const;
private:
    VehicleObjectPtr vehicleObject_;
    CarParametersPtr carParameters_;
};

using VehiclePtr = std::shared_ptr<Vehicle>;
