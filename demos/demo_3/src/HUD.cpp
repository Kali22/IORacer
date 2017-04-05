/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <HUD.h>
#include <sstream>

HUD::HUD(Vehicle &car) : vehicle(car),
                         sfmlData("x","impact",sf::Vector2f(50,50)),
                         boxData("y","impact",sf::Vector2f(50,300)) {

}

HUD::~HUD() {

}

void HUD::draw(sf::RenderWindow *window) {
    std::stringstream ss;
    sf::Vector2f mapPos = vehicle.GetPosition();
    sf::Vector2f boxPos = vehicle.GetBoxPosition();

    ss << "map_X: " << mapPos.x <<"\nmap_Y: "<<mapPos.y<<"\nmap_deg: "<<vehicle.GetAngle();
    sfmlData.SetString(ss.str());
    ss.str("");
    ss << "box_X: " << boxPos.x <<"\nbox_Y: "<<boxPos.y<<"\nbox_deg: "<<vehicle.GetBoxAngle()<<"\n";
    ss << "vel: " << vehicle.GetSpeed();
    boxData.SetString(ss.str());

    sfmlData.draw(window);
    boxData.draw(window);
}
