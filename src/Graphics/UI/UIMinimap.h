#pragma once


#include <UIElement.h>
#include <Texture.h>
#include <RealVec.h>

class UIMinimap : public UIElement {
public:
    UIMinimap(int id, std::string name, sf::FloatRect size, ActivityPtr
    activity, RealVec mapSize, TexturePtr texture);

    virtual void Render(RenderWindowPtr window);

    void Update(RealVec carPos, RealVec checkpointPos);

private:
    void UpdatePos(RealVec *origin, RealVec newPos);

    void DrawPos(RenderWindowPtr window, RealVec pos, sf::Color);

    RealVec mapSize_;
    TexturePtr texture_;
    RealVec carPos_;
    RealVec checkpointPos_;
};

using UIMinimapPtr = std::shared_ptr<UIMinimap>;
