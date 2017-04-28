//
// Created by pawel on 30.03.17.
//

#include <Race.h>

#include <Vehicle/TireControlE.h>


Race::Race(sf::RenderWindow *window, b2World *world, MapPtr map, HUDPtr hud, CheckPointManagerPtr checkPointManager) :
        Module(window), world_(world), map_(map), hud_(hud), checkPointManager_(checkPointManager) {};

void Race::Initialize(VehiclePtr vehicle) {
    sf::Vector2f pos = map_->GetStartPosition();
    vehicle_ = vehicle;
    vehicle_->Initialize(world_, (int) pos.x, (int) pos.y);

    // Prepare map
    checkPointManager_->Reset();
    hud_->Initialize(vehicle_, checkPointManager_);
    map_->AlignCameraViewSize(*window_);
    map_->SetCameraViewPosition(vehicle_->GetPosition());
    world_->SetContactListener(contactListener_.get());
}

void Race::Reset() {
    sf::Vector2f pos = map_->GetStartPosition();
    vehicle_->Reset((int) pos.x, (int) pos.y);
    checkPointManager_->Reset();
    map_->AlignCameraViewSize(*window_);
    map_->SetCameraViewPosition(vehicle_->GetPosition());
}

int Race::Run() {
    close_ = false;
    int carState = 0;
    bool interrupted = false;
    while (!close_) {
        interrupted = HandleEvents(carState);

        Update(carState);

        Render();
    }
    return interrupted;
}

bool Race::HandleEvents(int &carState) {
    sf::Event Event;
    while (window_->pollEvent(Event)) {
        // Close window : exit
        if (Event.type == sf::Event::Closed) {
            window_->close();
            close_ = true;
            return true;
        } else if (Event.type == sf::Event::KeyPressed) {
            if (Event.key.code == sf::Keyboard::Key::Escape) {
                close_ = true;
            }
            HandleKeyboard(Event.key, &carState, 1);
        } else if (Event.type == sf::Event::KeyReleased) {
            HandleKeyboard(Event.key, &carState, 0);
        }
    }
    return false;
}

void Race::Update(int &carState) {
/* Update physics object states */
    vehicle_->Update(carState, *map_);

/* Simulate the world */
    world_->Step(1 / 60.f, 8, 3);

/* Update game objects */
    checkPointManager_->Update();
    hud_->Update();
}

void Race::Render() {
    map_->SetCameraViewPosition(vehicle_->GetPosition());
    window_->clear(sf::Color::Black);
    map_->RenderBottomLayer(*window_);
    window_->setView(map_->GetCameraView());
    checkPointManager_->Draw(window_);
    vehicle_->Render(*window_);
    window_->setView(window_->getDefaultView());

    hud_->Draw(window_);
    window_->display();
}

VehiclePtr Race::GetVehicle() {
    return vehicle_;
}

void SetBitmask(int *reg, int mask, int type) {
    if (type)
        *reg |= mask;
    else
        *reg &= ~mask;
}

void Race::HandleKeyboard(sf::Event::KeyEvent Event, int *state, int type) {
    /// @TODO change to map
    switch (Event.code) {
        case sf::Keyboard::Key::Left:
            SetBitmask(state, LEFT, type);
            break;
        case sf::Keyboard::Key::Up:
            SetBitmask(state, UP, type);
            break;
        case sf::Keyboard::Key::Down:
            SetBitmask(state, DOWN, type);
            break;
        case sf::Keyboard::Key::Right:
            SetBitmask(state, RIGHT, type);
            break;
        case sf::Keyboard::Key::Space:
            SetBitmask(state, BRAKE, type);
            break;
        case sf::Keyboard::Key::D:
            if (type)
                hud_->DebugDisplayToggle();
            break;
        default:
            break;
    }
}
