//
// Created by pawel on 04.04.17.
//

#include <utility>
#include <iostream>

#include <Box2D.h>
#include <Object.h>
#include <GameObjects/CheckPoint/CheckPoint.h>
#include <ContactListener.h>

/** Return true if one of Entities is a car.
 *  If one of the entities is a car replace pointer so that the first one is the car.
 */
bool ContactListener::CheckIfCar(Object **entity1, Object **entity2) {
    if ((*entity2)->GetType() == OBJECT_TYPE_VEHICLE) {
        std::swap(*entity1, *entity2);
        return true;
    }
    if ((*entity1)->GetType() == OBJECT_TYPE_VEHICLE) {
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
bool ContactListener::GetUserData(b2Contact *contact, Object **entity, int
which) {
    b2Fixture *fixture = (!which ? contact->GetFixtureA() :
                          contact->GetFixtureB());
    if (!fixture) {
        return false;
    }
    b2Body *body = fixture->GetBody();
    if (!body) {
        return false;
    }
    *entity = (Object *) body->GetUserData();
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
    Object *entityA;
    Object *entityB;
    if (!GetUserData(contact, &entityA, 0) ||
        !GetUserData(contact, &entityB, 1)) {
        return false;
    }
    if (!CheckIfCar(&entityA, &entityB)) {
        return false;
    }
    if (entityB->GetType() != OBJECT_TYPE_CHECK_POINT) {
        return false;
    }
    *checkPoint = static_cast<CheckPoint *>(entityB);
    return true;
}
