/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#ifndef _HUD_H_
#define _HUD_H_


#include <Drawable.h>
#include <Vehicle.h>
#include <Entity/Text.h>

class HUD : public Drawable{
private:
    Text sfmlData;
    Text boxData;

    Vehicle &vehicle;
    Map &map;

public:
    HUD(Vehicle &car, Map &map);
    ~HUD();
    void draw(sf::RenderWindow *window);
};


#endif //HUD
