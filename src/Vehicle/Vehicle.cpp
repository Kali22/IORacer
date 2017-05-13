/**
 *  @file
 *  @ingroup vehicle
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <iostream>
#include <Vehicle.h>
#include <TireControlE.h>
#include <MathUtil.h>

Vehicle::Vehicle(CarParametersPtr params, VehicleObjectPtr vehicleObject)
        : vehicleObject_(vehicleObject),
          carParameters_(params) {
}

void Vehicle::Draw(RenderWindowPtr window) const {
    vehicleObject_->Draw(window);
}

RealVec Vehicle::GetPosition() const {
    return vehicleObject_->GetPosition();
}

void Vehicle::Update(int state, MapPtr map) {
    vehicleObject_->Update(state, map, carParameters_);
}

void Vehicle::Reset(int x, int y) {
    vehicleObject_->Reset(x, y);
}

float Vehicle::GetAngle() const {
    return vehicleObject_->GetAngle();
}

float Vehicle::GetBoxAngle() const {
    return vehicleObject_->GetBoxAngle();
}

float Vehicle::GetSpeed() const {
    return vehicleObject_->GetSpeed();
}

void Vehicle::PrintPos() const {
    vehicleObject_->PrintPos();
}

CarParametersPtr Vehicle::GetCarParameters() const {
    return carParameters_;
}

