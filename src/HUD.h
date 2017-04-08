#pragma once
/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <Drawable.h>
#include <Vehicle.h>
#include <Text.h>

class HUD : public Drawable {
public:
    HUD(Vehicle *car, Map *map);

    ~HUD();

    void Draw(sf::RenderWindow *window) const;

    void Initialize(Vehicle* vehicle);

    void Update();

private:
    Text sfmlData_;
    Text boxData_;

    Vehicle *vehicle_;
    Map *map_;
};

