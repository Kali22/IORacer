//
// Created by pawel on 04.04.17.
//

#include <utility>
#include <iostream>

#include <Box2D.h>
#include <Entity.h>
#include <CheckPoint.h>
#include <ContactListener.h>

/** Return true if one of Entitys is car.
 *  If one of entities is car replace pointer so that first one is a car.
 */
bool ContactListener::CheckIfCar(Entity** entity1, Entity** entity2) {
    if ((*entity2)->GetEntityType() == CAR) {
        std::cout << "Car\n";
        std::swap(*entity1, *entity2);
        return true;
    }
    if ((*entity1)->GetEntityType() == CAR) {
        std::cout << "Car\n";
        return true;
    }
    return false;
}

void ContactListener::BeginContact(b2Contact* contact) {
    std::cout << "Foo\n";

    CheckPoint* checkPoint;
    if (!GetCheckPointFromContact(contact, &checkPoint)) {
        return;
    }
    checkPoint->BeginContact();
}

ContactListener::ContactListener() {}

ContactListener::~ContactListener() {}

void ContactListener::EndContact(b2Contact* contact) {
    std::cout << "Foo end\n";
    CheckPoint* checkPoint;
    if (!GetCheckPointFromContact(contact, &checkPoint)) {
        return;
    }
    checkPoint->EndContact();
}


/** If contact is beetween car and check point return true and set checkPoint
 *  pointer to checkPoint from collision. Otherwise return false.
 */
bool ContactListener::GetCheckPointFromContact(
        b2Contact* contact, CheckPoint** checkPoint) {
    Entity* entityA = (Entity*)contact->GetFixtureA()->GetBody()
            ->GetUserData();
    Entity* entityB = (Entity*)contact->GetFixtureB()->GetBody()
            ->GetUserData();
    if (!entityA && !entityB) {
        std::cout << "Both nullptr\n";
    }

    if (!entityA || !entityB) {
        std::cout << "Null ptr\n";
        return false;
    }
    if (!CheckIfCar(&entityA, &entityB)) {
        std::cout << "Not car\n";
        return false;
    }
    if (entityB->GetEntityType() != CHECK_POINT) {
        std::cout << "Not check point\n";
        return false;
    }
    *checkPoint = static_cast<CheckPoint*>(entityB);
    return true;
}

