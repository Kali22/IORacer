/**
 *  @file
 *  @ingroup car
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#include <vehicle/Car.h>

#define SCALE 30.f

b2Body* CreateBox(b2World *World, int MouseX, int MouseY) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body *Body = World->CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f / 2) / SCALE, (48.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 3.f;
    FixtureDef.friction = 1.7f;
    FixtureDef.restitution = 0.5;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    return Body;
}

Car::Car() {

}

void Car::Initialize(b2World *world, int x, int y) {
    body = CreateBox(world, x, y);
    body->SetUserData(this);

    car_texture.loadFromFile("../resource/car.png");
    car_sprite.setTexture(car_texture);
    car_sprite.setOrigin(16.f, 24.f);
}

Car::~Car() {
    body->GetWorld()->DestroyBody(body);
}

void Car::Update(int state, float modifier) {
    updateFriction(modifier);
    updateDrive(state);
    updateTurn(state);
}

const sf::Drawable  &Car::GetSprite() {
    car_sprite.setPosition(SCALE * body->GetPosition().x,
                       SCALE * body->GetPosition().y);
    car_sprite.setRotation(body->GetAngle() * 180 / b2_pi);
    return car_sprite;
}

void Car::setCharacteristics(float maxForwardSpeed_, float maxBackwardSpeed_,
                             float maxDriveForce_) {
    maxForwardSpeed = maxForwardSpeed_;
    maxBackwardSpeed = maxBackwardSpeed_;
    maxDriveForce = maxDriveForce_;
}

b2Vec2 Car::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector(b2Vec2(1, 0));
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Car::getForwardVelocity() {
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Car::updateFriction(float modifier) {
    //lateral linear velocity
    float maxLateralImpulse = 2.5f;
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    if (impulse.Length() > maxLateralImpulse)
        impulse *= maxLateralImpulse / impulse.Length();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

    //angular velocity
    body->ApplyAngularImpulse(0.1f * body->GetInertia() *
                              -body->GetAngularVelocity(), true);

    //forward linear velocity
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    body->ApplyForce(modifier * dragForceMagnitude * currentForwardNormal,
                     body->GetWorldCenter(), true);
}

void Car::updateDrive(int controlState) {

    //find desired speed
    float desiredSpeed = 0;
    switch (controlState & (UP | DOWN)) {
        case UP:
            desiredSpeed = maxForwardSpeed;
            break;
        case DOWN:
            desiredSpeed = maxBackwardSpeed;
            break;
        default:
            return;//do nothing
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = body->GetWorldVector(b2Vec2(0, 1));
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (desiredSpeed > currentSpeed)
        force = maxDriveForce;
    else if (desiredSpeed < currentSpeed)
        force = -maxDriveForce;
    else
        return;
    body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter
            (), true);
}

void Car::updateTurn(int controlState) {
    float desiredTorque = 0;
    switch (controlState & (LEFT | RIGHT)) {
        case LEFT:
            desiredTorque = -15;
            break;
        case RIGHT:
            desiredTorque = +15;
            break;
        default:;//nothing
    }
    body->ApplyTorque(desiredTorque, true);
}

const sf::Vector2f &Car::GetPosition() const {
    return car_sprite.getPosition();
}

float Car::GetRotation() {
    return body->GetAngle() * 180 / b2_pi;
}

float Car::GetSpeed() {
    return body->GetLinearVelocity().Length();
}


