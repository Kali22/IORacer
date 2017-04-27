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

int Vehicle::GetEntityType() const {
    return CAR;
}

Vehicle::Vehicle(CarParametersPtr params, float scale) : carParameters_(params), scale_(scale) {}

Vehicle::~Vehicle() {
    body_->GetWorld()->DestroyJoint(fl_joint_);
    body_->GetWorld()->DestroyJoint(fr_joint_);
    body_->GetWorld()->DestroyJoint(bl_joint_);
    body_->GetWorld()->DestroyJoint(br_joint_);
    body_->GetWorld()->DestroyBody(body_);
}

void Vehicle::Render(sf::RenderWindow &window) {
    sprite_chassis_.setPosition(scale_ * body_->GetPosition().x,
                                scale_ * body_->GetPosition().y);
    sprite_chassis_.setRotation(MathUtil::RadianToDegree(body_->GetAngle()));
    window.draw(sprite_chassis_);
    for (auto &tire : tires_) {
        tire->Render(window);
    }
}

const sf::Vector2f &Vehicle::GetPosition() const {
    return sprite_chassis_.getPosition();
}

void Vehicle::Update(int state, Map &map) {
    UpdateFriction(map);
    UpdateDrive(state, map);
    UpdateTurn(state);
}

void Vehicle::CreateTire(b2World *world, b2RevoluteJoint **jointPtr, b2RevoluteJointDef &jointDef,
                         float bodyOffSetX, float bodyOffSetY,
                         float posX, float posY, TirePositionE positionFlags) {
    TirePtr tire = std::make_shared<Tire>(world, scale_, posX, posY, carParameters_, positionFlags);
    jointDef.bodyB = tire->body;
    jointDef.localAnchorA.Set(bodyOffSetX / scale_, bodyOffSetY / scale_);
    *jointPtr = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires_.push_back(tire);
}

void Vehicle::Initialize(b2World *world, int posX, int posY) {
    InitializeBody(world, posX, posY, 90);
    InitializeBodyFixture();
    CreateTires(world, posX, posY);

    texture_chassis_.loadFromFile("../resource/car.png");
    sprite_chassis_.setTexture(texture_chassis_);
    sprite_chassis_.setOrigin(16.f, 24.f);
}

void Vehicle::InitializeBodyFixture() {
    b2PolygonShape Shape;
    Shape.SetAsBox((16.f / 2) / scale_, (48.f / 2) / scale_);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 4.f;
    FixtureDef.friction = 1.7f;
    FixtureDef.restitution = 0.5;
    FixtureDef.shape = &Shape;
    body_->CreateFixture(&FixtureDef);
}

void Vehicle::InitializeBody(b2World *world, int posX, int posY, float angle) {
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(posX / scale_, posY / scale_);
    bodyDef.angle = MathUtil::DegreeToRadian(angle);
    bodyDef.type = b2_dynamicBody;
    body_ = world->CreateBody(&bodyDef);
    body_->SetUserData(this);
    body_->SetAngularVelocity(0);
    body_->SetLinearVelocity(b2Vec2(0, 0));
}

void Vehicle::CreateTires(b2World *world, int posX, int posY) {
    // Create TIRES
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body_;
    jointDef.referenceAngle = 0;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;        //with both these at zero...
    jointDef.upperAngle = 0;        //...the joint will not move
    jointDef.localAnchorB.SetZero();//joint anchor in tire is always center

    CreateTire(world, &fl_joint_, jointDef, -17.f, 18.f, posX, posY, LEFT_FRONT_TIRE);
    CreateTire(world, &fr_joint_, jointDef, 17.f, 18.f, posX, posY, RIGHT_FRONT_TIRE);
    CreateTire(world, &bl_joint_, jointDef, 17.f, -17.f, posX, posY, RIGHT_REAR_TIRE);
    CreateTire(world, &br_joint_, jointDef, -17.f, -17.f, posX, posY, LEFT_REAR_TIRE);
}

void Vehicle::Reset(int x, int y) {
    body_->SetAngularVelocity(0);
    body_->SetLinearVelocity(b2Vec2(0, 0));
    body_->SetTransform(b2Vec2(x / scale_, y / scale_), b2_pi / 2);
    fl_joint_->SetLimits(0, 0);
    fr_joint_->SetLimits(0, 0);
    for (auto tire : tires_) {
        tire->Reset(x / scale_, y / scale_);
    }
}

void Vehicle::UpdateFriction(Map &map) {
    for (auto &tire : tires_) {
        float modifier = map.GetFrictionModifier(tire->tireSprite.getPosition());
        tire->UpdateFriction(modifier);
    }
}

void Vehicle::UpdateDrive(int controlState, Map &map) {
    for (auto &tire : tires_) {
        float modifier = map.GetFrictionModifier(tire->tireSprite.getPosition());

        if (tire->IsFront())
            tire->UpdateDrive(controlState & ~UP, modifier);
        else
            tire->UpdateDrive(controlState & ~(BRAKE), modifier);
    }
}

void Vehicle::UpdateTurn(int controlState) {
    float turnSpeedPerSec = MathUtil::DegreeToRadian(carParameters_->steeringSpeed);
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = GetDesiredAngle(controlState);

    desiredAngle *= (1.f - 0.8f * abs((int) GetSpeed()) / carParameters_->maxForwardSpeed);
    float angleNow = fl_joint_->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;

    fl_joint_->SetLimits(newAngle, newAngle);
    fr_joint_->SetLimits(newAngle, newAngle);
}

float Vehicle::GetDesiredAngle(int controlState) {
    float desiredAngle = 0;
    float maxSteeringAngleRadians = MathUtil::DegreeToRadian(carParameters_->maxSteeringAngle);
    switch (controlState & (LEFT | RIGHT)) {
        case LEFT:
            desiredAngle = -maxSteeringAngleRadians;
            break;
        case RIGHT:
            desiredAngle = maxSteeringAngleRadians;
            break;
        default:;//nothing
    }
    return desiredAngle;
}

sf::Vector2f Vehicle::GetBoxPosition() const {
    sf::Vector2f pos;
    b2Vec2 boxPos = body_->GetPosition();
    pos.x = boxPos.x;
    pos.y = boxPos.y;
    return pos;
}

float Vehicle::GetAngle() const {
    return sprite_chassis_.getRotation();
}

float Vehicle::GetBoxAngle() const {
    return body_->GetAngle();
}

float Vehicle::GetSpeed() const {
    b2Vec2 vel = this->body_->GetLinearVelocity();
    return (float) sqrt(b2Dot(vel, vel));
}

float Vehicle::GetTireModifier(int i, Map &map) const {
    return map.GetFrictionModifier(tires_[i]->tireSprite.getPosition());
}

void Vehicle::PrintPos() const {
    std::cout << "Car " << body_->GetPosition().x << " "
              << body_->GetPosition().y << std::endl;
}

CarParametersPtr Vehicle::GetCarParameters() const {
    return carParameters_;
}
