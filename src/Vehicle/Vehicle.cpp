/**
 *  @file
 *  @ingroup vehicle
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <iostream>
#include <Vehicle.h>
#include <TireControlE.h>
#include <TirePositionE.h>
#include <MathUtil.h>

int Vehicle::GetEntityType() const {
    return CAR;
}

Vehicle::Vehicle(CarParametersPtr params, float scale) : carParameters_(params), scale_(scale) {}

Vehicle::~Vehicle() {
    body->GetWorld()->DestroyJoint(fl_joint);
    body->GetWorld()->DestroyJoint(fr_joint);
    body->GetWorld()->DestroyJoint(bl_joint);
    body->GetWorld()->DestroyJoint(br_joint);
    body->GetWorld()->DestroyBody(body);
}

void Vehicle::Render(sf::RenderWindow &window) {
    sprite_chassis.setPosition(scale_ * body->GetPosition().x,
                               scale_ * body->GetPosition().y);
    sprite_chassis.setRotation(MathUtil::RadianToDegree(body->GetAngle()));
    window.draw(sprite_chassis);
    for (auto &tire : tires) {
        tire->Render(window);
    }
}

const sf::Vector2f &Vehicle::GetPosition() const {
    return sprite_chassis.getPosition();
}

void Vehicle::Update(int state, Map &map) {
    UpdateFriction(map);
    UpdateDrive(state, map);
    UpdateTurn(state);
}

void Vehicle::CreateTire(b2World *world, b2RevoluteJoint **jointPtr, b2RevoluteJointDef &jointDef, float arg1, float arg2,
                         float x, float y, int positionFlags) {
    TirePtr tire = std::make_shared<Tire>(world, scale_, x, y, carParameters_, positionFlags);
    jointDef.bodyB = tire->body;
    jointDef.localAnchorA.Set(arg1 / scale_, arg2 / scale_);
    *jointPtr = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires.push_back(tire);
}

void Vehicle::Initialize(b2World *world, int x, int y) {
    //create car body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / scale_, y / scale_);
    bodyDef.angle = b2_pi / 2;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
    body->SetUserData(this);

    body->SetAngularVelocity(0);
    body->SetLinearVelocity(b2Vec2(0, 0));

    b2PolygonShape Shape;
    Shape.SetAsBox((16.f / 2) / scale_, (48.f / 2) / scale_);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 4.f;
    FixtureDef.friction = 1.7f;
    FixtureDef.restitution = 0.5;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);

    // Create TIRES
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.referenceAngle = 0;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;    //with both these at zero...
    jointDef.upperAngle = 0;    //...the joint will not move
    jointDef.localAnchorB.SetZero();//joint anchor in tire is always center

    // FRONT LEFT
    CreateTire(world, &fl_joint, jointDef, -17.f, 18.f, x, y, FRONT_TIRE | LEFT_TIRE);
    // FRONT RIGHT
    CreateTire(world, &fr_joint, jointDef, 17.f, 18.f, x, y, FRONT_TIRE | RIGHT_TIRE);
    // BACK RIGHT
    CreateTire(world, &bl_joint, jointDef, 17.f, -17.f, x, y, REAR_TIRE | RIGHT_TIRE);
    // BACK LEFT
    CreateTire(world, &br_joint, jointDef, -17.f, -17.f, x, y, REAR_TIRE | LEFT_TIRE);

    texture_chassis.loadFromFile("../resource/car.png");
    sprite_chassis.setTexture(texture_chassis);
    sprite_chassis.setOrigin(16.f, 24.f);
}

void Vehicle::Reset(int x, int y) {
    body->SetAngularVelocity(0);
    body->SetLinearVelocity(b2Vec2(0, 0));
    body->SetTransform(b2Vec2(x / scale_, y / scale_), b2_pi / 2);
    fl_joint->SetLimits(0, 0);
    fr_joint->SetLimits(0, 0);
    for (auto tire : tires) {
        tire->Reset(x / scale_, y / scale_);
    }
}

void Vehicle::UpdateFriction(Map &map) {
    for (auto &tire : tires) {
        float modifier = map.GetFrictionModifier(tire->tireSprite.getPosition());
        tire->UpdateFriction(modifier);
    }
}

void Vehicle::UpdateDrive(int controlState, Map &map) {
    for (auto &tire : tires) {
        float modifier = map.GetFrictionModifier(tire->tireSprite.getPosition());

        if (tire->GetTirePositionFlags() & REAR_TIRE)
            tire->UpdateDrive(controlState & ~(BRAKE), modifier);
        else
            tire->UpdateDrive(controlState & ~UP, modifier);
    }
}

void Vehicle::UpdateTurn(int controlState) {
    float turnSpeedPerSec = MathUtil::DegreeToRadian(carParameters_->steeringSpeed);
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch (controlState & (LEFT | RIGHT)) {
        case LEFT:
            desiredAngle = -MathUtil::DegreeToRadian(carParameters_->maxSteeringAngle);
            break;
        case RIGHT:
            desiredAngle = MathUtil::DegreeToRadian(carParameters_->maxSteeringAngle);
            break;
        default:;//nothing
    }
    desiredAngle *= (1.f - 0.8f * abs((int) GetSpeed()) / carParameters_->maxForwardSpeed);
    float angleNow = fl_joint->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    fl_joint->SetLimits(newAngle, newAngle);
    fr_joint->SetLimits(newAngle, newAngle);
}

sf::Vector2f Vehicle::GetBoxPosition() const {
    sf::Vector2f pos;
    b2Vec2 boxPos = body->GetPosition();
    pos.x = boxPos.x;
    pos.y = boxPos.y;
    return pos;
}

float Vehicle::GetAngle() const {
    return sprite_chassis.getRotation();
}

float Vehicle::GetBoxAngle() const {
    return body->GetAngle();
}

float Vehicle::GetSpeed() const {
    b2Vec2 vel = this->body->GetLinearVelocity();
    return (float) sqrt(b2Dot(vel, vel));
}

float Vehicle::GetTireModifier(int i, Map &map) const {
    return map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
}

void Vehicle::PrintPos() const {
    std::cout << "Car " << body->GetPosition().x << " "
              << body->GetPosition().y << std::endl;
}

CarParametersPtr Vehicle::GetCarParameters() const {
    return carParameters_;
}
