#pragma once

#include <bits/stdc++.h>
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <VisualObject.h>
#include <GameObjects/ObjectTypeE.h>

class Object {
public:
    Object(b2Body *body, VisualObjectPtr visualObject, ObjectTypeE type);

    b2Body *GetBody() const;

    VisualObjectPtr GetVisual() const;

    ObjectTypeE GetType() const;

    void SetPosition(const sf::Vector2f &pos);

    void SetPosition(float x, float y);

    void Move(const sf::Vector2f &dr);

    void Move(float offsetX, float offsetY);

    virtual void Rotate(float angle);

    virtual void SetRotation(float absoluteAngle);

    virtual void Rescale(float scale);

    virtual RealVec GetPosition() const;

    virtual void Draw(RenderWindowPtr window);

protected:
    ObjectTypeE type_;
    b2Body *body_;
    VisualObjectPtr visualObject_;
};

using ObjectPtr = std::shared_ptr<Object>;
