#pragma once

#include <RealVec.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

enum ObjectShapeE {
    OBJECT_SHAPE_RECT,
    OBJECT_SHAPE_CIRC
};

typedef struct {
    std::string name;
    std::string textureName;
    ObjectShapeE objectShape;

    RealVec size;
    float radius;
    float mass;
    bool dynamic;
} ObjectDesc;