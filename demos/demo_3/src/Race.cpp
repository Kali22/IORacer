//
// Created by pawel on 30.03.17.
//

#include <Race.h>
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
    std::vector<CheckPoint*> checkPoints = parser.ParseFile(
            "../resource/maps/map_0/checkpoints_list");
    checkPointManager_ = new CheckPointManager(checkPoints);
    vehicle.Initialize(&world, 1600, 2200);
    /// @TODO inject parameter rather than hardcode it
    vehicle.setCharacteristics(40, -10, 50);
    map.AlignCameraViewSize(window);
    map.SetCameraViewPosition(vehicle.GetPosition());
world.SetContactListener(&contactListener);
    checkPointManager_->StartTimer();
}

void Race::Run() {
    // Initialize game
    Initialize();

    int carState = 0;

    int cnt = 0;

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
//        float zoom = 0.8f + vehicle.GetSpeed()/70;
//        map.SetCameraViewZoom(zoom);
        window.clear(sf::Color::White);
        if (cnt == 120) {
            printf("Elapsed time: %f\n", checkPointManager_->GetElapsedTime()
                    .asSeconds());
            vehicle.PrintPos();
            cnt = 0;
        } else {
            cnt++;
        }
        //checkPoint->DebugPrint();
        map.RenderBottomLayer(window);
        window.setView(map.GetCameraView());
        checkPointManager_->DrawCheckPoints(&window);
//        map.SetCameraViewZoom(1.f / zoom);
//        window.setView(map.GetMinimapView());
//        window.draw(map.GetViewMap());
//        window.draw(vehicle.GetSprite());
        vehicle.Render(window);
        window.setView(window.getDefaultView());
        window.display();
    }
}
