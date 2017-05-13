//
// Created by pawel on 10.05.17.
//
#pragma once

#include <bits/stdc++.h>
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <Texture.h>
#include <Drawable.h>
#include <Movable.h>
#include <Scalable.h>
#include <Trackable.h>
#include <VisualObject.h>

enum objectType {
    CAR,
    CHECK_POINT,
    TIRE,
    BOX,
    STATIC_TIRE
};

// TODO is each of this interfaces necessary ?
class Object : public Drawable, public Movable, public Scalable, public
Trackable, public Rotatable  {
public:
    Object(b2Body* body, VisualObjectPtr visualObject);

    virtual void Draw(RenderWindowPtr window) const;

    virtual int GetObjectType() const = 0;

    virtual void SetPosition(const sf::Vector2f &pos);

    void SetPosition(float x, float y);

    void Rotate(float angle);

    void SetRotation(float absoluteAngle);

    RealVec GetPosition() const;

    void Move(const sf::Vector2f &dr);

    void Rescale(float scale);

    void Move(float offsetX, float offsetY);
protected:
    b2Body* body_;
    VisualObjectPtr visualObject_;
};

using ObjectPtr = std::shared_ptr<Object>;
