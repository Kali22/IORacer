//
// Created by pawel on 03.04.17.
//

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
