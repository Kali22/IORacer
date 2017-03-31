/**
 *  @file
 *  @ingroup car
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/31/17
 */

#include <Car.h>

#define SCALE 30.f

b2Body* CreateBox(b2World *World, int MouseX, int MouseY) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body *Body = World->CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 5.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    return Body;
}

Car::Car(b2World *world, int x, int y) {
    body = CreateBox(world, x, y);
    body->SetUserData(this);
}

Car::~Car() {
    body->GetWorld()->DestroyBody(body);
}

void Car::Update(int state) {
    updateFriction();
    updateDrive(state);
    updateTurn(state);
}

void Car::Draw(sf::RenderWindow &window, sf::Texture texture) {
    sf::Sprite Sprite;
    Sprite.setTexture(texture);
    Sprite.setOrigin(16.f, 16.f);
    Sprite.setPosition(SCALE * body->GetPosition().x,
                       SCALE * body->GetPosition().y);
    Sprite.setRotation(body->GetAngle() * 180 / b2_pi);
    window.draw(Sprite);
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

void Car::updateFriction() {
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
    body->ApplyForce(dragForceMagnitude * currentForwardNormal,
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
