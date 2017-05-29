#pragma once


#include <Box2D.h>
#include <SFML/Graphics/View.hpp>
#include <CheckPointObserver.h>
#include <Object.h>
#include <VisualObject.h>

/**
 * Check point is specific area. When car reach area enabled checkpoint
 * notify observer about change and set its state to disable.
 */
class CheckPoint : public Object {
public:
    CheckPoint(int id, b2Body *body, VisualObjectPtr visualObject);

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

    int GetId() const;

private:
    int playerId_;
    CheckPointObserver *observer_;
    bool enable_;
};
