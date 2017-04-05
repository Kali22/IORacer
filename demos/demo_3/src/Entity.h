//
// Created by pawel on 03.04.17.
//

#ifndef PROJECT_FIXTUREUSERDATA_H
#define PROJECT_FIXTUREUSERDATA_H

enum entityType {
    CAR,
    CHECK_POINT,
};


class Entity {
public:
    virtual int GetEntityType() = 0;
};


#endif //PROJECT_FIXTUREUSERDATA_H
