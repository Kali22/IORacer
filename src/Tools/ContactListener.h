//
// Created by pawel on 04.04.17.
//
#pragma once

#include <Box2D.h>
#include <CheckPoint.h>
#include <Object.h>

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *contact);

    void EndContact(b2Contact *contact);

private:
    bool GetUserData(b2Contact *contact, Object **entity, int which);

    bool CheckIfCar(Object **entity1, Object **entity2);

    bool GetCheckPointFromContact(b2Contact *contact, CheckPoint **checkPoint);
};

using ContactListenerPtr = std::shared_ptr<ContactListener>;
