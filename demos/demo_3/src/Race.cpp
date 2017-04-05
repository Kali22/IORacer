//
// Created by pawel on 30.03.17.
//

#include <Race.h>
#include <vehicle/Vehicle.h>

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
    vehicle.Initialize(&world, 1600, 2200);
    // Set initiial car params
    carParameters.activeTireModifier = 1.0f;
    carParameters.baseTireFriction = 1.0f;
    carParameters.maxBackwardSpeed = -20.f;
    carParameters.maxForwardSpeed = 60.f;
    carParameters.maxEnginePower = 30.f;
    carParameters.maxSteeringAngle = 20.f;
    carParameters.steeringSpeed = 120.0;

    map.AlignCameraViewSize(window);
    map.SetCameraViewPosition(vehicle.GetPosition());
}

void Race::Run() {
    // Initialize game
    Initialize();

    int carState = 0;

    while (window.isOpen()) {
        sf::Event Event;
        while (window.pollEvent(Event)) {
            // Close window : exit
            if (Event.type == sf::Event::Closed) {
                window.close();
            } else if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Key::Escape) {
                    window.close();
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
        window.clear(sf::Color::White);
//        float zoom = 0.8f + car.GetSpeed()/70;
//        map.SetCameraViewZoom(zoom);
        map.RenderBottomLayer(window);
        window.setView(map.GetCameraView());
//        map.SetCameraViewZoom(1.f / zoom);
//        window.setView(map.GetMinimapView());
//        window.draw(map.GetViewMap());
//        window.draw(car.GetSprite());
        vehicle.Render(window);
        window.setView(window.getDefaultView());

        hud.draw(&window);
        window.display();
    }
}
