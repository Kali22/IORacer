#pragma once

enum entityType {
    CAR,
    CHECK_POINT,
    TIRE,
};


class Entity {
public:
    virtual int GetEntityType() const = 0;
};
