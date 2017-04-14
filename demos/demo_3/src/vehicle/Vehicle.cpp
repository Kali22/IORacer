/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <iostream>

#include <Vehicle.h>
#include <Tools/Map.h>
#include "Vehicle.h"
#include "CarParams.h"
#include <CarControlE.h>
#include <Tools/Entity.h>

#define SCALE 30.f

int Vehicle::GetEntityType() const {
    return CAR;
}

Vehicle::Vehicle(CarParameters &params) : carParameters(params) {}

Vehicle::~Vehicle() {
    body->GetWorld()->DestroyJoint(fl_joint);
    body->GetWorld()->DestroyJoint(fr_joint);
    body->GetWorld()->DestroyJoint(bl_joint);
    body->GetWorld()->DestroyJoint(br_joint);
    for (int i = 0; i < tires.size(); ++i)
        tires[i]->~Tire();
    body->GetWorld()->DestroyBody(body);
}

void Vehicle::Render(sf::RenderWindow &window) {
    sprite_chassis.setPosition(SCALE * body->GetPosition().x,
                               SCALE * body->GetPosition().y);
    sprite_chassis.setRotation(body->GetAngle() * 180.f / b2_pi);
    window.draw(sprite_chassis);
    tires[0]->Render(window);
    tires[1]->Render(window);
    tires[2]->Render(window);
    tires[3]->Render(window);
}

const sf::Vector2f &Vehicle::GetPosition() const {
    return sprite_chassis.getPosition();
}

void Vehicle::Update(int state, Map *map) {
    updateFriction(*map); // TODO change to const &
    updateDrive(state, *map);
    updateTurn(state);
}

void Vehicle::Initialize(b2World *world, int x, int y) {
    //create car body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
    bodyDef.angle = 0;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
    body->SetUserData(this);


    b2PolygonShape Shape;
    Shape.SetAsBox((16.f / 2) / SCALE, (48.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 4.f;
    FixtureDef.friction = 1.7f;
    FixtureDef.restitution = 0.5;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);

    // Create TIRES
    // FRONT LEFT
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.referenceAngle = 0;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;//with both these at zero...
    jointDef.upperAngle = 0;//...the joint will not move
    jointDef.localAnchorB.SetZero();//joint anchor in tire is always center

    Tire *tire = new Tire(world, 0, 0, 0, CarParametersPtr(), 0);
    jointDef.bodyB = tire->body;
    jointDef.referenceAngle = 0;
    jointDef.localAnchorA.Set(-17.f / SCALE, 18.f / SCALE);
    fl_joint = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires.push_back(tire);

    // FRONT RIGHT
    tire = new Tire(world, 0, 0, 0, CarParametersPtr(), 0);
    jointDef.bodyB = tire->body;
    jointDef.referenceAngle = 0;
    jointDef.localAnchorA.Set(17.f / SCALE, 18.f / SCALE);
    fr_joint = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires.push_back(tire);

    // BACK RIGHT
    tire = new Tire(world, 0, 0, 0, CarParametersPtr(), 0);
    jointDef.bodyB = tire->body;
    jointDef.referenceAngle = 0;
    jointDef.localAnchorA.Set(17.f / SCALE, -17.f / SCALE);
    br_joint = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires.push_back(tire);

    // BACK LEFT
    tire = new Tire(world, 0, 0, 0, CarParametersPtr(), 0);
    jointDef.bodyB = tire->body;
    jointDef.referenceAngle = 0;
    jointDef.localAnchorA.Set(-17.f / SCALE, -17.f / SCALE);
    bl_joint = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires.push_back(tire);

    texture_chassis.loadFromFile("../resource/car.png");
    sprite_chassis.setTexture(texture_chassis);
    sprite_chassis.setOrigin(16.f, 24.f);
}

void Vehicle::updateFriction(Map &map) {
    for (int i = 0; i < 4; i++) {
        float modifier = map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
        tires[i]->UpdateFriction(modifier);
    }
}

void Vehicle::updateDrive(int controlState, Map &map) {
    for (int i = 0; i < 4; i++) {
        float modifier = map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
        tires[i]->UpdateDrive(controlState, modifier);
    }
}

void Vehicle::updateTurn(int controlState) {
    float turnSpeedPerSec = carParameters.steeringSpeed * b2_pi / 180.f;
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch (controlState & (LEFT | RIGHT)) {
        case LEFT:
            desiredAngle = -carParameters.maxSteeringAngle * b2_pi / 180.f;
            break;
        case RIGHT:
            desiredAngle = carParameters.maxSteeringAngle * b2_pi / 180.f;
            break;
        default:;//nothing
    }
    desiredAngle *= (1.f - abs(GetSpeed()) / carParameters.maxForwardSpeed);
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

float Vehicle::GetAngle() {
    return sprite_chassis.getRotation();
}

float Vehicle::GetBoxAngle() {
    return body->GetAngle();
}

float Vehicle::GetSpeed() {
    b2Vec2 vel = this->body->GetLinearVelocity();
    return sqrt(b2Dot(vel,vel));
}

float Vehicle::GetTireModifier(int i, Map &map) {
    return map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
}

void Vehicle::PrintPos() {
    std::cout << "Car " << body->GetPosition().x << " "
              << body->GetPosition().y << std::endl;

}
