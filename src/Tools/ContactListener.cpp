//
// Created by pawel on 04.04.17.
//

#include <utility>
#include <iostream>

#include <Box2D.h>
#include <Tools/Entity.h>
#include <CheckPoint.h>
#include <Tools/ContactListener.h>

/** Return true if one of Entities is a car.
 *  If one of the entities is a car replace pointer so that the first one is the car.
 */
bool ContactListener::CheckIfCar(Entity **entity1, Entity **entity2) {
    if ((*entity2)->GetEntityType() == CAR) {
        std::swap(*entity1, *entity2);
        return true;
    }
    if ((*entity1)->GetEntityType() == CAR) {
        return true;
    }
    return false;
}

void ContactListener::BeginContact(b2Contact *contact) {
    CheckPoint *checkPoint;
    if (!GetCheckPointFromContact(contact, &checkPoint)) {
        return;
    }
    checkPoint->BeginContact();
}

void ContactListener::EndContact(b2Contact *contact) {}

/**
 * if which is 0 check for A body, otherwise for B body
 */
bool ContactListener::GetUserData(b2Contact *contact, Entity **entity, int which) {
    b2Fixture *fixture = (!which ? contact->GetFixtureA() :
                          contact->GetFixtureB());
    if (!fixture) {
        return false;
    }
    b2Body *body = fixture->GetBody();
    if (!body) {
        return false;
    }
    *entity = (Entity *) body->GetUserData();
    if (!(*entity)) {
        return false;
    }
    return true;
}

/** If contact is beetween car and check point return true and set checkPoint
 *  pointer to checkPoint from collision. Otherwise return false.
 */
bool ContactListener::GetCheckPointFromContact(
        b2Contact *contact, CheckPoint **checkPoint) {
    Entity *entityA;
    Entity *entityB;
    if (!GetUserData(contact, &entityA, 0) ||
        !GetUserData(contact, &entityB, 1)) {
        return false;
    }
    if (!CheckIfCar(&entityA, &entityB)) {
        return false;
    }
    if (entityB->GetEntityType() != CHECK_POINT) {
        return false;
    }
    *checkPoint = static_cast<CheckPoint *>(entityB);
    return true;
}
