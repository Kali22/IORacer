//
// Created by pawel on 10.05.17.
//
#include <Box2D/Box2D.h>
#include <Drawable.h>
#include "VisualObject.h"
#include "Object.h"

Object::Object(b2Body *body, VisualObjectPtr visualObject)
        : body_(body), visualObject_(visualObject) { }

void Object::Draw(RenderWindowPtr window) const {
    // TODO add wraper in order to not convert vectors
    b2Vec2 pos = body_->GetPosition();

    // Reset position to match physics
    visualObject_->SetPosition(pos.x, pos.y);
    visualObject_->SetRotation(body_->GetAngle());
    visualObject_->Draw(window);
}

void Object::SetPosition(const sf::Vector2f &pos) {
    SetPosition(pos.x, pos.y);
}

void Object::SetPosition(float x, float y) {
    body_->SetTransform(b2Vec2(x, y), body_->GetAngle());
    visualObject_->SetPosition(x, y);
}

void Object::Move(const sf::Vector2f &dr) {
    Move(dr.x, dr.y);
}

void Object::Move(float offsetX, float offsetY) {
    b2Vec2 pos = body_->GetPosition();
    body_->SetTransform(b2Vec2(pos.x + offsetX, pos.y + offsetY),
                        body_->GetAngle());
    visualObject_->Move(offsetX, offsetY);
}

// Angle in radians.
void Object::Rotate(float angle) {
    float curAngle = body_->GetAngle();
    SetRotation(curAngle + angle);
}

void Object::SetRotation(float absoluteAngle) {
    b2Vec2 pos = body_->GetPosition();
    body_->SetTransform(pos, absoluteAngle);
    visualObject_->SetRotation(absoluteAngle);
}

/**
 * Rescales sprite size to match global physical scale (pixs per meter).
 */
void Object::Rescale(float scale) {
    visualObject_->Rescale(scale);
}

RealVec Object::GetPosition() const {
    b2Vec2 pos = body_->GetPosition();
    return RealVec(pos.x, pos.y);
}
