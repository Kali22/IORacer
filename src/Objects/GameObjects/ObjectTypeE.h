#pragma once


#include <string>
#include <bits/stdc++.h>

/* All possible objects types in game.
 * It's important to match proper object name in object configuration file.*/
enum ObjectTypeE {
    OBJECT_TYPE_VEHICLE,
    OBJECT_TYPE_WHEEL,
    OBJECT_TYPE_CHECK_POINT,
    OBJECT_TYPE_TIRE,
    OBJECT_TYPE_BOX,
    OBJECT_TYPE_CONE,
    OBJECT_TYPE_STONE,
    OBJECT_TYPE_BOUND
};

extern std::map<ObjectTypeE, std::string> ObjectsMap;
