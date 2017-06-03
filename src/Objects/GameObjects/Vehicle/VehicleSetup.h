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

struct VehicleSetup {
    float massBalance;
    float vehicleMass;
    float steeringAngleSpeed; // In degs per sec
    VehicleTransmissionTypeE transmissionType;
    VehicleBrakesTypeE brakesType;
};
