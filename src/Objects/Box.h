#pragma once

#include <Drawable.h>
#include <RealVec.h>
#include "VisualObject.h"
#include "Object.h"


class Box : public Object {
public:
    Box(b2World *world, VisualObjectPtr visualObject);

    virtual int GetObjectType() const;
private:
    static b2Body* InitializeBody(b2World *world, const RealVec& size);

    static void InitializeFixture(b2Body* body, const RealVec& size);
};
