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

static const float defaultSteeringAngle = 45;
static const VehicleBrakesTypeE defaultBrakesType = BRAKES_FRONT;
static const float defaultMassBalance = 0.45;
static const VehicleTransmissionTypeE defaultTransmissionType = TRANSMISSION_REAR;
static const float defautlVehicleMass = 300;

class VehicleSetup {
public:
    VehicleSetup()
            : massBalance(defaultMassBalance), vehicleMass(defautlVehicleMass),
              steeringAngleSpeed(defaultSteeringAngle),
              transmissionType(defaultTransmissionType),
              brakesType(defaultBrakesType) {}

    float massBalance;
    float vehicleMass;
    float steeringAngleSpeed; // In degs per sec
    VehicleTransmissionTypeE transmissionType;
    VehicleBrakesTypeE brakesType;
};

