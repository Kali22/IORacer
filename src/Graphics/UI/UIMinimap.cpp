#include "UIMinimap.h"

#include <Texture.h>
#include <Activity.h>


UIMinimap::UIMinimap(int id, std::string name, sf::FloatRect size, ActivityPtr
activity, TexturePtr texture)
        : UIElement(id, name, size, activity), texture_(texture) {
    // TODO compute scale
}

void UIMinimap::Render(RenderWindowPtr window) {
    UIElement::Render(window);
    //window->draw(bounds_);
}

void UIMinimap::Update(RealVec carPos, RealVec checkpointPos) {
    UpdatePos(&carPos_, carPos);
    UpdatePos(&checkpointPos_, checkpointPos);
}

void UIMinimap::UpdatePos(RealVec* origin, RealVec newPos) {
    origin->x = newPos.x;
    origin->y = newPos.y;
}
