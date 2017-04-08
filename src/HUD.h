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
    HUD(VehiclePtr car, MapPtr map);

    ~HUD();

    void Draw(sf::RenderWindow *window) const;

    void Initialize(VehiclePtr vehicle);

    void Update();

private:
    Text sfmlData_;
    Text boxData_;

    VehiclePtr vehicle_;
    MapPtr map_;
};

using HUDPtr = std::shared_ptr<HUD>;
