//
// Created by pawel on 30.03.17.
//

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <set>

#include "Race.hpp"

#define SCALE 30.f

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

enum {
    LEFT = 0x1,
    RIGHT = 0x2,
    UP = 0x4,
    DOWN = 0x8
};


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


class Car {
public:
    Car(b2World *world, int x, int y) {
        body = CreateBox(world, x, y);
        body->SetUserData(this);
    }

    ~Car() {
        body->GetWorld()->DestroyBody(body);
    }

    void Update(int state) {
        updateFriction();
        updateDrive(state);
        updateTurn(state);
    }

    void Draw(sf::RenderWindow &window, sf::Texture texture) {
        sf::Sprite Sprite;
        Sprite.setTexture(texture);
        Sprite.setOrigin(16.f, 16.f);
        Sprite.setPosition(SCALE * body->GetPosition().x,
                           SCALE * body->GetPosition().y);
        Sprite.setRotation(body->GetAngle() * 180 / b2_pi);
        window.draw(Sprite);
    }

    void setCharacteristics(float maxForwardSpeed_, float maxBackwardSpeed_,
                            float maxDriveForce_) {
        maxForwardSpeed = maxForwardSpeed_;
        maxBackwardSpeed = maxBackwardSpeed_;
        maxDriveForce = maxDriveForce_;
    }

private:
    b2Vec2 getLateralVelocity() {
        b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
        return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
    }

    b2Vec2 getForwardVelocity() {
        b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
        return b2Dot( currentForwardNormal, body->GetLinearVelocity() ) * currentForwardNormal;
    }

    void updateFriction() {
        //lateral linear velocity
        float maxLateralImpulse = 2.5f;
        b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
        if ( impulse.Length() > maxLateralImpulse )
            impulse *= maxLateralImpulse / impulse.Length();
        body->ApplyLinearImpulse( impulse, body->GetWorldCenter(), true);

        //angular velocity
        body->ApplyAngularImpulse( 0.1f * body->GetInertia() *
                                   -body->GetAngularVelocity(), true);

        //forward linear velocity
        b2Vec2 currentForwardNormal = getForwardVelocity();
        float currentForwardSpeed = currentForwardNormal.Normalize();
        float dragForceMagnitude = -2 * currentForwardSpeed;
        body->ApplyForce( dragForceMagnitude * currentForwardNormal,
                          body->GetWorldCenter() ,true);
    }

    void updateDrive(int controlState) {

        //find desired speed
        float desiredSpeed = 0;
        switch ( controlState & (UP|DOWN) ) {
            case UP:   desiredSpeed = maxForwardSpeed;  break;
            case DOWN: desiredSpeed = maxBackwardSpeed; break;
            default: return;//do nothing
        }

        //find current speed in forward direction
        b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
        float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

        //apply necessary force
        float force = 0;
        if ( desiredSpeed > currentSpeed )
            force = maxDriveForce;
        else if ( desiredSpeed < currentSpeed )
            force = -maxDriveForce;
        else
            return;
        body->ApplyForce( force * currentForwardNormal, body->GetWorldCenter
                (), true);
    }

    void updateTurn(int controlState) {
        float desiredTorque = 0;
        switch ( controlState & (LEFT|RIGHT) ) {
            case LEFT:  desiredTorque = 15;  break;
            case RIGHT: desiredTorque = -15; break;
            default: ;//nothing
        }
        body->ApplyTorque(desiredTorque, true);
    }


    b2Body *body;
    float maxForwardSpeed;
    float maxBackwardSpeed;
    float maxDriveForce;
};


void HandleKeyboard(sf::Event::KeyEvent Event, int *state) {
    switch (Event.code) { // TODO change to map
        case sf::Keyboard::Key::A:
            *state |= LEFT;
            break;
        case sf::Keyboard::Key::W:
            *state |= UP;
            break;
        case sf::Keyboard::Key::S:
            *state |= DOWN;
            break;
        case sf::Keyboard::Key::D:
            *state |= RIGHT;
            break;
        default:
            break;
    }
}


void Race::Run() {
    /** Prepare the world */
    b2Vec2 Gravity(0.f, 0.f);
    b2World World(Gravity);

    sf::Texture BoxTexture;
    BoxTexture.loadFromFile("box.png");
    int carState = 0;
    Car car(&World, 300, 300);
    car.setCharacteristics(100, -20, 150);

    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                window.close();

            if (Event.type == sf::Event::KeyPressed) {
                HandleKeyboard(Event.key, &carState);
            }
        }

        /** Simulate the world */
        car.Update(carState);
        World.Step(1 / 60.f, 8, 3);

        window.clear(sf::Color::White);
        car.Draw(window, BoxTexture);
        window.display();
        carState = 0;
    }
}
