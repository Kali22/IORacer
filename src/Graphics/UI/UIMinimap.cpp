#include <UIMinimap.h>
#include <Activity.h>

UIMinimap::UIMinimap(int id, std::string name, sf::FloatRect size, ActivityPtr activity, RealVec mapSize,
                     TexturePtr texture) :
        UIElement(id, name, size, activity),
        mapSize_(mapSize),
        texture_(texture) {
    SetOutlineThickness(0.5f);
    SetOutlineColor(sf::Color(0, 0, 0, 200));
}

void UIMinimap::Render(RenderWindowPtr window) {
    UIElement::Render(window);
    DrawPos(window, carPos_, sf::Color(255, 50, 0, 250));
    DrawPos(window, checkpointPos_, sf::Color(0, 250, 200, 250));
}

void UIMinimap::Update(RealVec carPos, RealVec checkpointPos) {
    UpdatePos(&carPos_, carPos);
    UpdatePos(&checkpointPos_, checkpointPos);
}

void UIMinimap::UpdatePos(RealVec *origin, RealVec newPos) {
    origin->x = newPos.x;
    origin->y = newPos.y;
}

void UIMinimap::DrawPos(RenderWindowPtr window, RealVec posOnMap, sf::Color color) {
    sf::CircleShape point(5);
    point.setFillColor(color);
    point.setOutlineColor(sf::Color(0, 0, 0, 150));

    SetScale();

    sf::Vector2f pos = GetPos(posOnMap);
    point.setPosition(pos);
    window->draw(point);
}

void UIMinimap::SetScale() {
    float scale = bounds_.getGlobalBounds().height / mapSize_.y;
    carPos_.SetScale(scale);
    checkpointPos_.SetScale(scale);
}

sf::Vector2f UIMinimap::GetPos(RealVec posOnMap) {
    sf::Vector2f pos = bounds_.getPosition();
    sf::Vector2f scaledPos = posOnMap.GetScaledVector();
    pos.x += scaledPos.x;
    pos.y += scaledPos.y;
    return pos;
}