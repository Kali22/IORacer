#pragma once

enum VehicleTransmissionTypeE {
    TRANSMISSION_FRONT,
    TRANSMISSION_REAR,
    TRANSMISSION_4X4,
};

enum VehicleBrakesTypeE {
    BRAKES_FRONT,
    BRAKES_REAR
};

struct VehicleSetupT {
    float massBalance;
    float vehicleMass;
    float enginePowerMax;
    float steeringAngleSpeed; // In degs per sec
    float steeringAngleMax;
    float aerodynamicFriction;
    VehicleTransmissionTypeE transmissionType;
    VehicleBrakesTypeE brakesType;
};