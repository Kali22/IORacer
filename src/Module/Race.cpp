//
// Created by pawel on 30.03.17.
//

#include "Race.h"

#include <CheckPointParser.h>
#include <Vehicle/CarControlE.h>

//#ifndef DEGTORAD
//#define DEGTORAD 0.0174532925199432957f
//#define RADTODEG 57.295779513082320876f
//#endif

void setclr(int *reg, int mask, int type) {
    if (type)
        *reg |= mask;
    else
        *reg &= ~mask;
}

void HandleKeyboard(sf::Event::KeyEvent Event, int *state, int type) {
    /// @TODO change to map
    switch (Event.code) {
        case sf::Keyboard::Key::Left:
            setclr(state, LEFT, type);
            break;
        case sf::Keyboard::Key::Up:
            setclr(state, UP, type);
            break;
        case sf::Keyboard::Key::Down:
            setclr(state, DOWN, type);
            break;
        case sf::Keyboard::Key::Right:
            setclr(state, RIGHT, type);
            break;
        case sf::Keyboard::Key::B:
            setclr(state, BRAKE, type);
            break;
        default:
            break;
    }
}

void Race::Initialize() {
    // Prepare map
    map.LoadMap("map_0", "Mapa testowa");
    /// TODO add race builder
    CheckPointParser parser(&world, 30); // scale
    /// @TODO move checkPointsParser to map Load
    std::vector<CheckPoint *> checkPoints = parser.ParseFile(
            "../resource/maps/map_0/checkpoints_list");
    checkPointManager_ = new CheckPointManager(checkPoints);
    vehicle.Initialize(&world, 1600, 2200);

    // Set initiial car params
    carParameters.activeTireModifier = 1.0f;
    carParameters.baseTireFriction = 1.0f;
    carParameters.maxBackwardSpeed_ = -20.f;
    carParameters.maxForwardSpeed_ = 60.f;
    carParameters.maxEnginePower_ = 30.f;
    carParameters.maxSteeringAngle = 20.f;
    carParameters.steeringSpeed = 120.0;


    /// @TODO inject parameter rather than hardcode it
    //Vehicle.setCharacteristics(40, -10, 50);

    map.AlignCameraViewSize(*window_);
    map.SetCameraViewPosition(vehicle.GetPosition());
    world.SetContactListener(&contactListener);
    checkPointManager_->StartTimer();
}

int Race::run() {

    int carState = 0;

    int cnt = 0;
    close_ = false;
    while (!close_) {
        sf::Event Event;
        while (window_->pollEvent(Event)) {
            // Close window : exit
            if (Event.type == sf::Event::Closed) {
                close_ = true;
            } else if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Key::Escape) {
                    close_ = true;
                }
                HandleKeyboard(Event.key, &carState, 1);
            } else if (Event.type == sf::Event::KeyReleased) {
                HandleKeyboard(Event.key, &carState, 0);
            }
        }

        /* Update states */
        vehicle.Update(carState, map);

        /* Simulate the world */
        world.Step(1 / 60.f, 8, 3);

        /* Rendering */
        map.SetCameraViewPosition(vehicle.GetPosition());
        window_->clear(sf::Color::White);
//        float zoom = 0.8f + Vehicle.GetSpeed()/70;
//        map.SetCameraViewZoom(zoom);
        window_->clear(sf::Color::White);
        if (cnt == 120) {
            printf("Elapsed time: %f\n", checkPointManager_->GetElapsedTime()
                    .asSeconds());
            vehicle.PrintPos();
            cnt = 0;
        } else {
            cnt++;
        }
        //checkPoint->DebugPrint();
        map.RenderBottomLayer(*window_);
        window_->setView(map.GetCameraView());
        checkPointManager_->DrawCheckPoints(window_);
//        map.SetCameraViewZoom(1.f / zoom);
//        window_->setView(map.GetMinimapView());
//        window_->draw(map.GetViewMap());
//        window_->draw(Vehicle.GetSprite());
        vehicle.Render(*window_);
        window_->setView(window_->getDefaultView());

        hud.draw(window_);
        window_->display();
    }
    return 0;
}

Vehicle *Race::getVehicle() {
    return &vehicle;
}