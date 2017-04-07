#pragma once
/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <Drawable.h>
#include <Vehicle.h>
#include <Entity/Text.h>

class HUD : public Drawable{
public:
    HUD(Vehicle &car, Map &map);
    ~HUD();
    void Draw(sf::RenderWindow *window);

private:
    Text sfmlData;
    Text boxData;

    Vehicle &vehicle;
    Map &map;
};

