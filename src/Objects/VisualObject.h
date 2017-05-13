#pragma once

#include <bits/stdc++.h>
#include <Box2D/Box2D.h>
#include <RealVec.h>
#include <Texture.h>
#include <Drawable.h>
#include <Movable.h>
#include <Scalable.h>
#include <Trackable.h>
#include <Rotatable.h>
#include "ObjectDesc.h"

/**
 * @TODO Należy dodać jakąś warstwę pod spodem, movable musi respektować skalę!
 */
class VisualObject : public Drawable, public Movable, public Scalable, public
Trackable, public Rotatable {
public:
    VisualObject(ObjectDesc objectDesc, TexturePtr texture);

    void Draw(RenderWindowPtr window) const;

    void SetPosition(const sf::Vector2f &pos);

    void SetPosition(float x, float y);

    void Rotate(float angle);

    void SetRotation(float absoluteAngle);

    RealVec GetPosition() const;

    void Move(const sf::Vector2f &dr);

    void Rescale(float scale);

    void Move(float offsetX, float offsetY);

    virtual RealVec GetSize() const;
private:
    void UpdateSpritePosition();

    std::string name_;

    RealVec position_;
    ObjectShapeE objectShape_;

    RealVec size_;
    float radius_;
    sf::Sprite sprite_;
};

using VisualObjectPtr = std::shared_ptr<VisualObject>;