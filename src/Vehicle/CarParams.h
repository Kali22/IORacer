/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#pragma once

class CarParameters {
public:
    /*-------- Driving power modifiers ---------*/
    /// Maximum speed foreward
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

using CarParametersPtr = CarParameters *;
