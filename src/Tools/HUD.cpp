/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <Tools/HUD.h>

HUD::HUD(VehiclePtr vehicle, MapPtr map)
        : vehicle_(vehicle),
          sfmlData_("x", "impact", sf::Vector2f(50, 50), 20),
          boxData_("y", "impact", sf::Vector2f(50, 300), 20),
          map_(map) {}

HUD::~HUD() {}

void HUD::Initialize(VehiclePtr vehicle) {
    vehicle_ = vehicle;
}

void HUD::Update() {
    if (vehicle_ == nullptr) {
        return;
    }
    std::stringstream ss;
    sf::Vector2f mapPos = vehicle_->GetPosition();
    sf::Vector2f boxPos = vehicle_->GetBoxPosition();

    ss << "map_X: " << mapPos.x << "\nmap_Y: " << mapPos.y << "\n";
    ss << "map_deg: " << vehicle_->GetAngle();

    sfmlData_.SetText(ss.str());
    ss.str("");
    ss << "box_X: " << boxPos.x << "\nbox_Y: " << boxPos.y << "\n";
    ss << "box_deg: " << vehicle_->GetBoxAngle() << "\n";
    ss << "vel: " << vehicle_->GetSpeed() << "\n";
    ss << "fl_wheel: " << vehicle_->GetTireModifier(0, *map_) << "\n";
    ss << "fr_wheel: " << vehicle_->GetTireModifier(1, *map_) << "\n";
    ss << "bl_wheel: " << vehicle_->GetTireModifier(3, *map_) << "\n";
    ss << "br_wheel: " << vehicle_->GetTireModifier(2, *map_) << "\n";
    boxData_.SetText(ss.str());
}

void HUD::Draw(sf::RenderWindow *window) const {
    sfmlData_.Draw(window);
    boxData_.Draw(window);
}

