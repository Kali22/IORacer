#pragma once


#include <Texture.h>
#include <RealVec.h>
#include <UIElement.h>

class UIMinimap : public UIElement {
public:
    UIMinimap(int id, std::string name, sf::FloatRect size,
              WeakActivityPtr activity, RealVec mapSize, TexturePtr texture);

    virtual void Render(RenderWindowPtr window);

    void Update(RealVec carPos, RealVec checkpointPos);

private:
    void UpdatePos(RealVec *origin, RealVec newPos);

    void DrawPos(RenderWindowPtr window, RealVec pos, sf::Color);

    void SetScale();

    sf::Vector2f GetPos(RealVec posOnMap);

    RealVec mapSize_;
    TexturePtr texture_;
    RealVec carPos_;
    RealVec checkpointPos_;
};

using UIMinimapPtr = std::shared_ptr<UIMinimap>;
