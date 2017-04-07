//
// Created by pawel on 30.03.17.
//

#include <Race.h>

#include <vehicle/Vehicle.h>
#include <CheckPoint.h>
#include <CheckPointManager.h>
#include <CheckPointParser.h>

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

Race::Race(sf::RenderWindow *win, b2World *world, Map *map, Vehicle *vehicle,
           HUD *hud, CheckPointManager* checkPointManager)
        : window_(win),
          world_(world),
          map_(map),
          vehicle_(vehicle),
          hud_(hud),
          checkPointManager_(checkPointManager) {}


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
    vehicle_->Initialize(world_, 1600, 2200);

    map_->AlignCameraViewSize(*window_);
    map_->SetCameraViewPosition(vehicle_->GetPosition());
    world_->SetContactListener(&contactListener);
    checkPointManager_->StartTimer();
}

void Race::Run() {
    // Initialize game
    Initialize();

    int carState = 0;

    int cnt = 0;

    while (window_->isOpen()) {
        sf::Event Event;
        while (window_->pollEvent(Event)) {
            // Close window : exit
            if (Event.type == sf::Event::Closed) {
                window_->close();
            } else if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Key::Escape) {
                    window_->close();
                }
                HandleKeyboard(Event.key, &carState, 1);
            } else if (Event.type == sf::Event::KeyReleased) {
                HandleKeyboard(Event.key, &carState, 0);
            }
        }

        /* Update states */
        vehicle_->Update(carState, map_);

        /* Simulate the world */
        world_->Step(1 / 60.f, 8, 3);

        /* Rendering */
        map_->SetCameraViewPosition(vehicle_->GetPosition());
        window_->clear(sf::Color::White);
        window_->clear(sf::Color::White);
        if (cnt == 120) {
            printf("Elapsed time: %f\n", checkPointManager_->GetElapsedTime()
                    .asSeconds());
            vehicle_->PrintPos();
            cnt = 0;
        } else {
            cnt++;
        }
        map_->RenderBottomLayer(*window_);
        window_->setView(map_->GetCameraView());
        checkPointManager_->Draw(window_);

        vehicle_->Render(*window_);
        window_->setView(window_->getDefaultView());

        hud_->Update();
        hud_->Draw(window_);
        window_->display();
    }
}
