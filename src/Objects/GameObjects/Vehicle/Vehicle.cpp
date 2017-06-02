#include <Vehicle.h>
#include <MathUtil.h>
#include <CheckPoint.h>

enum ControllerStateE {
    CTRL_STATE_ACC = 0x01,
    CTRL_STATE_REV = 0x02,
    CTRL_STATE_LEFT = 0x04,
    CTRL_STATE_RIGHT = 0x08,
    CTRL_STATE_BRK = 0x10,
};

Vehicle::Vehicle(int id, b2Body *body, VisualObjectPtr chassis, std::vector<WheelPtr> &&wheels,
                 const VehicleSetupT &setup, CarConfigurationPtr carConfiguration, MapPtr map) :
        Object(body, chassis, OBJECT_TYPE_VEHICLE),
        wheels_(std::move(wheels)),
        vehicleSetup_(setup),
        carConfiguration_(carConfiguration),
        map_(map),
        activeCheckpoint_(nullptr),
        id_(id),
        controllerState_(0) {
    body_->SetUserData(this);
    InitializeWheels();
}

void Vehicle::Accelerate(bool state) {
    if (state)
        controllerState_ |= CTRL_STATE_ACC;
    else
        controllerState_ &= ~CTRL_STATE_ACC;
}

void Vehicle::TurnLeft(bool state) {
    if (state)
        controllerState_ |= CTRL_STATE_LEFT;
    else
        controllerState_ &= ~CTRL_STATE_LEFT;
}

void Vehicle::TurnRight(bool state) {
    if (state)
        controllerState_ |= CTRL_STATE_RIGHT;
    else
        controllerState_ &= ~CTRL_STATE_RIGHT;
}

void Vehicle::Brake(bool state) {
    if (state)
        controllerState_ |= CTRL_STATE_BRK;
    else
        controllerState_ &= ~CTRL_STATE_BRK;
}

void Vehicle::Update(float dt) {
    UpdateModifiers();
    UpdateFriction(dt);
    UpdateDrive();
    UpdateTurn(dt);
}

Vehicle::~Vehicle() {
    body_->GetWorld()->DestroyJoint(fl_joint_);
    body_->GetWorld()->DestroyJoint(fr_joint_);
    body_->GetWorld()->DestroyJoint(bl_joint_);
    body_->GetWorld()->DestroyJoint(br_joint_);
    body_->GetWorld()->DestroyBody(body_);
}

void Vehicle::InitializeWheels() {
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body_;
    jointDef.referenceAngle = 0;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;        //with both these at zero...
    jointDef.upperAngle = 0;        //...the joint will not move
    jointDef.localAnchorB.SetZero();//joint anchor in tire is always center

    wheels_[0]->InitializeWheel(&fl_joint_, jointDef, -1.33f, 1.7f, WHEEL_LEFT_FRONT);
    wheels_[1]->InitializeWheel(&fr_joint_, jointDef, 1.33f, 1.7f, WHEEL_RIGHT_FRONT);
    wheels_[2]->InitializeWheel(&bl_joint_, jointDef, -1.33f, -1.7f, WHEEL_LEFT_REAR);
    wheels_[3]->InitializeWheel(&br_joint_, jointDef, 1.33f, -1.7f, WHEEL_RIGHT_REAR);
}

void Vehicle::Draw(RenderWindowPtr window) {
    Object::Draw(window);
    for (auto &wheel : wheels_) {
        wheel->Draw(window);
    }
}

void Vehicle::UpdateFriction(float dt) {
    for (auto &wheel : wheels_) {
        wheel->UpdateFriction(dt);
    }
}

void Vehicle::UpdateDrive() {
    if (controllerState_ & (CTRL_STATE_ACC | CTRL_STATE_REV)) {
        if (enginePowerNow_ < carConfiguration_->GetEnginePowerMax()) {
            enginePowerNow_ += carConfiguration_->GetEnginePowerMax() / 10.f;
        }
        float torque = enginePowerNow_ * 0.5f;
        torque = (controllerState_ & CTRL_STATE_REV ? -torque : torque);
        switch (vehicleSetup_.transmissionType) {
            case TRANSMISSION_4X4:
                torque *= 0.5f;
                for (auto &wheel : wheels_)
                    wheel->UpdateDrive(torque);
                break;

            case TRANSMISSION_FRONT:
                for (auto &wheel : wheels_)
                    if (wheel->IsFront())
                        wheel->UpdateDrive(torque);
                break;

            case TRANSMISSION_REAR:
                for (auto &wheel : wheels_)
                    if (!wheel->IsFront())
                        wheel->UpdateDrive(torque);
                break;
        }
    } else {
        enginePowerNow_ = 0;
    }

    if (controllerState_ & CTRL_STATE_BRK) {
        for (auto &wheel : wheels_) {
            if ((vehicleSetup_.brakesType == BRAKES_FRONT) && wheel->IsFront())
                wheel->Brake();
            else if (vehicleSetup_.brakesType == BRAKES_REAR && !wheel->IsFront())
                wheel->Brake();
        }
    } else {
        for (auto &wheel : wheels_)
            wheel->ReleaseBrake();
    }
}

void Vehicle::UpdateTurn(float dt) {
    float turnSpeedPerSec = MathUtil::DegreeToRadian(vehicleSetup_.steeringAngleSpeed);
    float turnPerTimeStep = turnSpeedPerSec * dt;
    float desiredAngle = GetDesiredAngle();
    float angleNow = fl_joint_->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    fl_joint_->SetLimits(newAngle, newAngle);
    fr_joint_->SetLimits(newAngle, newAngle);
}

void Vehicle::UpdateModifiers() {
    /// @TODO HERE UPDATE DIFFERENT PARAMS
    for (auto &wheel : wheels_) {
        std::cerr << "Vehicle " << id_ << ":" << std::endl;
        float modifier = map_->GetFrictionModifier(wheel->GetPosition());
        float load = 9.81f * vehicleSetup_.vehicleMass * 0.5f;
        if (wheel->IsFront())
            load *= 1.f - vehicleSetup_.massBalance;
        else
            load *= vehicleSetup_.massBalance;
        wheel->UpdateModifiers(modifier, load, carConfiguration_->GetAerodynamicFriction());
    }
}

void Vehicle::ChangeVehicleSetup(const VehicleSetupT setup) {
    vehicleSetup_ = setup;
}

float Vehicle::GetDesiredAngle() {
    float desiredAngle = 0;
    float maxSteeringAngleRadians = MathUtil::DegreeToRadian(carConfiguration_->GetSteeringAngleMax());
    switch (controllerState_ & (CTRL_STATE_LEFT | CTRL_STATE_RIGHT)) {
        case CTRL_STATE_LEFT:
            desiredAngle = -maxSteeringAngleRadians;
            break;
        case CTRL_STATE_RIGHT:
            desiredAngle = maxSteeringAngleRadians;
            break;
        default:;//nothing
    }
    return desiredAngle;
}

void Vehicle::Rescale(float scale) {
    Object::Rescale(scale);
    for (auto &wheel : wheels_) {
        wheel->Rescale(scale);
    }
}

void Vehicle::Reset(float x, float y, float rot) {
    body_->SetAngularVelocity(0);
    body_->SetLinearVelocity(b2Vec2(0, 0));
    body_->SetTransform(b2Vec2(x, y), rot);
    for (auto &wheel : wheels_) {
        wheel->Reset(x, y, rot);
    }
}

void Vehicle::Reverse(bool state) {
    if (state)
        controllerState_ |= CTRL_STATE_REV;
    else
        controllerState_ &= ~CTRL_STATE_REV;
}

void Vehicle::PrintDiagnostic() {
    printf("ctrl state: %#08X\n", controllerState_);
    printf("body_: x: %f, y: %f, a: %f\n", body_->GetPosition().x, body_->GetPosition().y, body_->GetAngle());
    for (auto &wheel : wheels_)
        printf("wheel %d: x: %f, y: %f, a: %f\n", wheel->GetWheelType(), wheel->GetBody()->GetPosition().x,
               wheel->GetBody()->GetPosition().y, wheel->GetBody()->GetAngle());
    printf("speed: m/s:%f, km/h:%f [x: %f, y: %f]\n", body_->GetLinearVelocity().Length(),
           body_->GetLinearVelocity().Length() * 0.001 * 3600., body_->GetLinearVelocity().x,
           body_->GetLinearVelocity().y);

}

void Vehicle::DrawPrivate(RenderWindowPtr window) {
    if (activeCheckpoint_ != nullptr) {
        activeCheckpoint_->Draw(window);
    }
}

void Vehicle::SetActiveCheckpoint(CheckPointPtr active) {
    activeCheckpoint_ = active;
}

int Vehicle::GetId() const {
    return id_;
}
