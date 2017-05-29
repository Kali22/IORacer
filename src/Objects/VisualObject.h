#pragma once


#include <bits/stdc++.h>
#include <SFML/Graphics/Sprite.hpp>
#include <RealVec.h>
#include <Texture.h>
#include <ObjectDesc.h>
#include <GraphicsCommon.h>

class VisualObject {
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
