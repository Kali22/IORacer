#pragma once

#include <VisualObject.h>
#include <Object.h>
#include <VisualObject.h>

class TruckTire : public Object {
public:
    TruckTire(b2World *world, VisualObjectPtr visualObject);

    virtual int GetObjectType() const;
private:
    static b2Body* InitializeBody(b2World *world, const RealVec& size);

    static void InitializeFixture(b2Body* body, const RealVec& size);
};