//
// Created by pawel on 03.04.17.
//

#pragma once

enum entityType {
    CAR,
    CHECK_POINT,
    TIRE,
    BOX,
    STATIC_TIRE
};


class Entity {
public:
    virtual int GetEntityType() const = 0;
};
