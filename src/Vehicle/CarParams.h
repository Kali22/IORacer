/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#pragma once

class CarParameters {
public:
    CarParameters() {
        // Set default value
        activeTireModifier = 1.f;
        baseTireFriction = 1.f;
        maxBackwardSpeed = -20.f;
        maxForwardSpeed = 30.f;
        maxEnginePower = 10.f;
        maxSteeringAngle = 20.f;
        steeringSpeed = 40.f;
    }

    /*-------- Driving power modifiers ---------*/
    /// Maximum speed forward
    float maxForwardSpeed;
    /// Maximum speed backward
    float maxBackwardSpeed;
    /// Engine power, how fast we accelerate
    float maxEnginePower;

    /*---------- Friction modifiers ------------*/
    /// Tires base friction
    float baseTireFriction;
    /// Tire modifier
    float activeTireModifier;

    /*----------- Turning modifiers ------------*/
    /// Max angle
    float maxSteeringAngle;
    /// How fast you're turning your wheel
    float steeringSpeed;
};

using CarParametersPtr = std::shared_ptr<CarParameters>;
