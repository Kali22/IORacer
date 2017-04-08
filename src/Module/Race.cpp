//
// Created by pawel on 30.03.17.
//

#include <Race.h>

#include <CheckPointParser.h>
#include <Vehicle/CarControlE.h>

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

void Race::Initialize(Vehicle *vehicle) {

    vehicle_ = vehicle;
    // Prepare map
    vehicle_->Initialize(world_, 1600, 2200);

    hud_->Initialize(vehicle_);
    map_->AlignCameraViewSize(*window_);
    map_->SetCameraViewPosition(vehicle_->GetPosition());
    world_->SetContactListener(&contactListener_);
    checkPointManager_->Initialize();
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
        vehicle_->Update(carState, *map_);

        /* Simulate the world */
        world_->Step(1 / 60.f, 8, 3);
        hud_->Update();
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

        hud_->Draw(window_);
        window_->display();
    }
    // delete car from world
    return 0;
}

Vehicle *Race::getVehicle() {
    return vehicle_;
}