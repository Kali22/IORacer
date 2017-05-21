#include "RealVec.h"

RealVec::RealVec() : sf::Vector2f(0, 0), scale_(1.f) {

}

RealVec::RealVec(float scalePixInMeters) : sf::Vector2f(0, 0), scale_(scalePixInMeters) {

}

RealVec::RealVec(const b2Vec2& vec) : RealVec(vec.x, vec.y) {}

RealVec::RealVec(const sf::Vector2f &vec) : sf::Vector2f(vec), scale_(1.f) {
}

RealVec::RealVec(const sf::Vector2f &vec, float scalePixInMeters) :
        sf::Vector2f(vec.x / scalePixInMeters, vec.y / scalePixInMeters),
        scale_(scalePixInMeters) {

}

float RealVec::GetScale() const {
    return scale_;
}

void RealVec::SetScale(float scalePixInMeters) {
    scale_ = scalePixInMeters;
}

sf::Vector2f RealVec::GetScaledVector() const {
    return scale_ * sf::Vector2f(x, y);
}

RealVec::RealVec(float x, float y) : Vector2(x, y) {

}

RealVec &RealVec::operator=(const RealVec &vec) {
    x = vec.x;
    y = vec.y;
    scale_ = vec.scale_;
    return *this;
}

RealVec &RealVec::operator=(const sf::Vector2f &vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}

RealVec::RealVec(float x, float y, float scale) : Vector2(x, y), scale_(scale) {

}

