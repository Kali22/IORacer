/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/1/17
 */

#include <iostream>

#include <Vehicle.h>
#include <CarControlE.h>

int Vehicle::GetEntityType() const {
    return CAR;
}

Vehicle::Vehicle(CarParametersPtr params, float scale) : carParameters_(params), scale_(scale) {}

Vehicle::~Vehicle() {
    body->GetWorld()->DestroyJoint(fl_joint);
    body->GetWorld()->DestroyJoint(fr_joint);
    body->GetWorld()->DestroyJoint(bl_joint);
    body->GetWorld()->DestroyJoint(br_joint);
    //for (int i = 0; i < tires.size(); ++i)
    //    tires[i].reset(); //tires[i]->~Tire();
    body->GetWorld()->DestroyBody(body);
}

void Vehicle::Render(sf::RenderWindow &window) {
    sprite_chassis.setPosition(scale_ * body->GetPosition().x,
                               scale_ * body->GetPosition().y);
    sprite_chassis.setRotation(body->GetAngle() * 180.f / b2_pi);
    window.draw(sprite_chassis);
    for (int i = 0; i < 4; i++) {
        tires[i]->Render(window);
    }
}

const sf::Vector2f &Vehicle::GetPosition() const {
    return sprite_chassis.getPosition();
}

void Vehicle::Update(int state, Map &map) {
    updateFriction(map);
    updateDrive(state, map);
    updateTurn(state);
}

void Vehicle::createTire(
        b2World *world, b2RevoluteJoint **jointPtr, b2RevoluteJointDef &jointDef, float arg1, float arg2) {
    TirePtr tire = std::make_shared<Tire>(world, scale_);
    jointDef.bodyB = tire->body;
    jointDef.referenceAngle = 0;
    jointDef.localAnchorA.Set(arg1 / scale_, arg2 / scale_);
    *jointPtr = (b2RevoluteJoint *) world->CreateJoint(&jointDef);
    tires.push_back(tire);
}

void Vehicle::Initialize(b2World *world, int x, int y) {
    //create car body
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x / scale_ + 25, y / scale_ + 22);
    bodyDef.angle = b2_pi;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
    body->SetUserData(this);


    b2PolygonShape Shape;
    Shape.SetAsBox((16.f / 2) / scale_, (48.f / 2) / scale_);
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

    // FRONT LEFT
    createTire(world, &fl_joint, jointDef, -17.f, 18.f);
    // FRONT RIGHT
    createTire(world, &fr_joint, jointDef, 17.f, 18.f);
    // BACK RIGHT
    createTire(world, &bl_joint, jointDef, 17.f, -17.f);
    // BACK LEFT
    createTire(world, &br_joint, jointDef, -17.f, -17.f);

    texture_chassis.loadFromFile("../resource/car.png");
    sprite_chassis.setTexture(texture_chassis);
    sprite_chassis.setOrigin(16.f, 24.f);
}

void Vehicle::Reset(int x, int y) {
    body->SetTransform(b2Vec2(x / scale_, y / scale_), 0);
    fl_joint->SetLimits(0, 0);
    fr_joint->SetLimits(0, 0);
    for (auto t : tires) {
        t->Reset();
    }
}

void Vehicle::updateFriction(Map &map) {
    for (int i = 0; i < 4; i++) {
        float modifier = map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
        tires[i]->updateFriction(modifier, *carParameters_);
    }
}

void Vehicle::updateDrive(int controlState, Map &map) {
    for (int i = 0; i < 4; i++) {
        float modifier = map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
        tires[i]->UpdateDrive(controlState, modifier, *carParameters_);
    }
}

void Vehicle::updateTurn(int controlState) {
    float turnSpeedPerSec = carParameters_->steeringSpeed * b2_pi / 180.f;
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch (controlState & (LEFT | RIGHT)) {
        case LEFT:
            desiredAngle = -carParameters_->maxSteeringAngle * b2_pi / 180.f;
            break;
        case RIGHT:
            desiredAngle = carParameters_->maxSteeringAngle * b2_pi / 180.f;
            break;
        default:;//nothing
    }
    desiredAngle *= (1.f - abs(GetSpeed()) / carParameters_->maxForwardSpeed);
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
    return sqrt(b2Dot(vel, vel));
}

float Vehicle::GetTireModifier(int i, Map &map) {
    return map.GetFrictionModifier(tires[i]->tireSprite.getPosition());
}

void Vehicle::PrintPos() {
    std::cout << "Car " << body->GetPosition().x << " "
              << body->GetPosition().y << std::endl;
}

CarParametersPtr Vehicle::getCarParameters() {
    return carParameters_;
}
