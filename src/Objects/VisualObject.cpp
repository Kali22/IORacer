#include "VisualObject.h"


VisualObject::VisualObject(ObjectDesc objectDesc, TexturePtr texture) :
        name_(objectDesc.name),
        objectShape_(objectDesc.objectShape),
        size_(objectDesc.size),
        radius_(objectDesc.radius),
        position_(RealVec()) {
    if (objectShape_ == OBJECT_SHAPE_CIRC) {
        size_.x = 2 * radius_;
        size_.y = 2 * radius_;
    }
    sprite_.setTexture(*texture->GetTexture());
    auto size = sprite_.getGlobalBounds();
    // Origin in graphics center
    sprite_.setOrigin(size.width * .5f, size.height * .5f);
    std::cerr << "Instance of \"" << objectDesc.name << "\" created!\n";
}

void VisualObject::Draw(RenderWindowPtr window) const {
    window->draw(sprite_);
}

void VisualObject::SetPosition(const sf::Vector2f &pos) {
    position_ = pos;
    UpdateSpritePosition();
}


void VisualObject::SetPosition(float x, float y) {
    position_ = sf::Vector2f(x, y);
    UpdateSpritePosition();
}

void VisualObject::Move(const sf::Vector2f &dr) {
    position_ += dr;
    UpdateSpritePosition();
}

void VisualObject::Move(float offsetX, float offsetY) {
    position_.x += offsetX;
    position_.y += offsetY;
    UpdateSpritePosition();
}

void VisualObject::Rotate(float angle) {
    sprite_.rotate(angle);
}

void VisualObject::SetRotation(float absoluteAngle) {
    sprite_.setRotation(absoluteAngle);
}

void VisualObject::UpdateSpritePosition() {
    sprite_.setPosition(position_.GetScaledVector());
}


/**
 * Rescales sprite size to match global physical scale (pixs per meter).
 */
void VisualObject::Rescale(float scale) {
    auto spriteSize = sprite_.getGlobalBounds();
    float scaleY = scale * size_.y / spriteSize.height;
    float scaleX = scale * size_.x / spriteSize.width;
    if (scaleX < 0.99 * scaleY || 1.01 * scaleY < scaleX) {
        std::cerr << "Object <" << name_ << ">: scales X and Y doesn't match!\n";
    }
    sprite_.setScale(scaleX, scaleY);
    position_.SetScale(scale);
    std::cerr << "Object <" << name_ << ">: scale set " << scale <<"!\n";
}

RealVec VisualObject::GetPosition() const {
    return position_;
}

RealVec VisualObject::GetSize() const {
    return size_;
}
