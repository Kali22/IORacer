//
// Created by pawel on 04.04.17.
//

#include <Box2D.h>
#include <Tools/Entity.h>
#include <CheckPoint.h>

#ifndef PROJECT_CONTACTLISTENER_H
#define PROJECT_CONTACTLISTENER_H

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);

    ContactListener();

    ~ContactListener();
private:
    bool GetUserData(b2Contact* contact, Entity** entity, int which);

    bool CheckIfCar(Entity** entity1, Entity** entity2);

    bool GetCheckPointFromContact(b2Contact* contact, CheckPoint** checkPoint);
};

#endif //PROJECT_CONTACTLISTENER_H
