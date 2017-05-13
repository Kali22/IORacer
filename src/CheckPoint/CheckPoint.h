#pragma once
//
// Created by pawel on 03.04.17.
//

#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <CheckPointObserver.h>
#include <Object.h>
#include <VisualObject.h>

/**
 * Check point is specyfic area. When car reach area enabled checkpoint
 * notify observer about change and set its state to disable.
 */
class CheckPoint : public Object {
public:
    // TODO set size in object manager RealVec
    CheckPoint(b2World* world, VisualObjectPtr
            visualObject);

    virtual int GetObjectType() const;

    void SetEnable(bool value);

    bool IsEnable() const;

    void Draw(RenderWindowPtr window);
    /**
     * Set observer who is notifed each time when enabled checkpoint is
     * reached by car.
     */
    void SetObserver(CheckPointObserver *observer);

    /**
     * Set enable to false and notify observer. Should be called by contact
     * listener when car reach checkpoint.
     */
    void BeginContact();

    void EndContact();
private:
    static b2Body* InitializeBody(b2World* world, const RealVec& size);
    CheckPointObserver *observer_;
    bool enable_;
};

using CheckPointPtr = std::shared_ptr<CheckPoint>;
