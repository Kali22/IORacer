/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <HUD.h>
#include <sstream>

HUD::HUD(Vehicle &car, Map &map) : vehicle(car),
                                   sfmlData("x","impact",sf::Vector2f(50,50)),
                                   boxData("y","impact",sf::Vector2f(50,300)), map(map)
{

}

HUD::~HUD() {

}

void HUD::draw(sf::RenderWindow *window) {
    std::stringstream ss;
    sf::Vector2f mapPos = vehicle.GetPosition();
    sf::Vector2f boxPos = vehicle.GetBoxPosition();

    ss << "map_X: " << mapPos.x <<"\nmap_Y: "<<mapPos.y<<"\nmap_deg: "<<vehicle.GetAngle();
    sfmlData.setText(ss.str());
    ss.str("");
    ss << "box_X: " << boxPos.x <<"\nbox_Y: "<<boxPos.y<<"\nbox_deg: "<<vehicle.GetBoxAngle()<<"\n";
    ss << "vel: " << vehicle.GetSpeed()<<"\n";
    ss << "fl_wheel: " << vehicle.GetTireModifier(0, map) << "\n";
    ss << "fr_wheel: " << vehicle.GetTireModifier(1, map) << "\n";
    ss << "bl_wheel: " << vehicle.GetTireModifier(3, map) << "\n";
    ss << "br_wheel: " << vehicle.GetTireModifier(2, map) << "\n";
    boxData.setText(ss.str());

    sfmlData.draw(window);
    boxData.draw(window);
}
