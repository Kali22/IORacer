#include "Object.h"

#include <Drawable.h>
#include <MathUtil.h>

Object::Object(b2Body *body, VisualObjectPtr visualObject, ObjectTypeE type)
        : body_(body), visualObject_(visualObject), type_(type) {}

b2Body *Object::GetBody() const {
    return body_;
}

VisualObjectPtr Object::GetVisual() const {
    return VisualObjectPtr();
}

ObjectTypeE Object::GetType() const {
    return type_;
}

void Object::Draw(RenderWindowPtr window) {
    b2Vec2 pos = body_->GetPosition();
    visualObject_->SetPosition(pos.x, pos.y);
    visualObject_->SetRotation(MathUtil::RadianToDegree(body_->GetAngle()));
    visualObject_->Draw(window);
}

void Object::SetPosition(const sf::Vector2f &pos) {
    SetPosition(pos.x, pos.y);
}

void Object::SetPosition(float x, float y) {
    body_->SetTransform(b2Vec2(x, y), body_->GetAngle());
}

void Object::Move(const sf::Vector2f &dr) {
    Move(dr.x, dr.y);
}

void Object::Move(float offsetX, float offsetY) {
    b2Vec2 pos = body_->GetPosition();
    body_->SetTransform(b2Vec2(pos.x + offsetX, pos.y + offsetY),
                        body_->GetAngle());
}

void Object::Rotate(float angle) {
    // Angle in radians.
    float curAngle = body_->GetAngle();
    SetRotation(curAngle + angle);
}

void Object::SetRotation(float absoluteAngle) {
    b2Vec2 pos = body_->GetPosition();
    body_->SetTransform(pos, absoluteAngle);
}

void Object::Rescale(float scale) {
    visualObject_->Rescale(scale);
}

RealVec Object::GetPosition() const {
    b2Vec2 pos = body_->GetPosition();
    visualObject_->SetPosition(pos.x, pos.y);
    return visualObject_->GetPosition();
}
