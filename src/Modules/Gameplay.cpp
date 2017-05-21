#include "../Managers/ActivityManager.h"
#include "Gameplay.h"
#include <CheckPointManager.h>

Gameplay::Gameplay(const std::string &mapName, int laps)
        : Activity("race"),
          laps_(laps),
          mapName_(mapName),
          firstPlayerName_(""), secondPlayerName_(""), isOver_(false),
          contactListener_(std::make_shared<ContactListener>()) {
}

sf::Clock clk;

void Gameplay::Init() {
    world_ = new b2World(b2Vec2(0, 0));
    objectManager_ = std::make_shared<ObjectManager>(activityManager_->GetTextureManager(), world_);
    mapManager_ = std::make_shared<MapManager>(activityManager_->GetTextureManager(), objectManager_);
    map_ = mapManager_->CreateMap(mapName_);
    scene_ = std::make_shared<Scene>(map_);
    world_->SetContactListener(contactListener_.get());

    /// @TODO player manager-> get player vehicle attributes and create player vehicle
    if (firstPlayerName_.empty()) {
        fprintf(stderr, "One player at least required!\n");
        ExitGame();
    }
    PrepareFirstPlayer();
    if (!secondPlayerName_.empty()) {
        PrepareSecondPlayer();
    }
    world_->Step(1.f / 60.f, 8, 6); // Init step
    gameState_ = GAMEPLAY_STATE_PREPARE;
    globalTime_ = 0.f;
    PrepareUIForPrepareState();
}

void Gameplay::PrintState() {
    float sec = clk.restart().asSeconds();
    printf(">>>> fps: %f, time: %f\n", 1 / sec, sec);
    printf("game state: %d\n", gameState_);
    printf("global time: %f\n", globalTime_);
    firstPlayerVehicle_->PrintDiagnostic();
}

void Gameplay::Run() {
//    PrintState();
    Update();
    Render();
}

void Gameplay::End() {
    free(world_);
}

void Gameplay::EventAction(Event event) {
    if (event.type == SFML_EVENT) {
        if (event.sfmlEvent.type == sf::Event::KeyPressed) {
            HandleKey(event.sfmlEvent.key, true);
        } else if (event.sfmlEvent.type == sf::Event::KeyReleased) {
            HandleKey(event.sfmlEvent.key, false);
        }
    }

}

void Gameplay::HandleKey(sf::Event::KeyEvent event, bool state) {
    switch (gameState_) {
        case GAMEPLAY_STATE_PREPARE:
            if (state)
                HandleKeyInPrepareState(event);
            break;
        case GAMEPLAY_STATE_RUNNING:
            HandleKeyInGameState(event, state);
            break;
        case GAMEPLAY_STATE_PAUSE:
            if (state)
                HandleKeyInPauseState(event);
            break;
        case GAMEPLAY_STATE_END:
            if (state)
                HandleKeyInEndState(event);
            break;
    }
}

void Gameplay::SetSecondPlayer(const std::string &name) {
    secondPlayerName_ = name;
}

void Gameplay::SetFirstPlayer(const std::string &name) {
    firstPlayerName_ = name;
}

void Gameplay::ExitGame() {
    activityManager_->RemoveActivity("race");
    activityManager_->SetAsActive("player_selector");
}

void Gameplay::Render() {
    /* Rendering */
    RendererPtr renderer = activityManager_->GetRenderer();
    renderer->Clear();
    if (secondPlayerVehicle_ == nullptr)
        renderer->RenderScene(scene_, VIEW_TYPE_SINGLE);
    else
        renderer->RenderScene(scene_, VIEW_TYPE_MULTI);
    renderer->RenderUI(userInterface_);
    renderer->Display();
}

void Gameplay::Update() {
    float dt = 1.f / 60.f;
    switch (gameState_) {
        case GAMEPLAY_STATE_PREPARE:
            globalTime_ += dt;
            UpdateUIInPrepareState();
            if (globalTime_ >= preparationTimeInSeconds) {
                globalTime_ = 0;
                gameState_ = GAMEPLAY_STATE_RUNNING;
                PrepareHUD();
            }
            break;

        case GAMEPLAY_STATE_RUNNING:
            UpdateGame();
            break;

        case GAMEPLAY_STATE_PAUSE:
            UpdateUIInPauseState();
            break;

        case GAMEPLAY_STATE_END:
            UpdateUIInEndState();
            break;
    }
}

void Gameplay::UpdateUIInPrepareState() {
    UITextBoxPtr title = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("title"));
    std::stringstream ss;
    ss << "Start in " << (int) ceil(preparationTimeInSeconds - globalTime_) << " seconds!";
    title->SetText(ss.str());
}

void Gameplay::UpdateUIInPauseState() {

}

void Gameplay::PrepareUIForPrepareState() {
    UIBoxPtr back = userInterface_->CreateBox("background", sf::FloatRect(0.5, 0.5, 1, 1));
    back->SetBackgroundColor(sf::Color(0, 0, 0, 80));
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "Prepare to race!", 60,
                                                       sf::FloatRect(0.5, 0.075, 1, 0.2));
    SetTitleStyle(title);
}

void Gameplay::UpdateHUD() {
    UITextBoxPtr title = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("time"));
    std::stringstream ss;
    ss << (int) (globalTime_ / 60.) << ":" << ((int) globalTime_) % 60 << ":" << (int) (globalTime_ * 100) % 100;
    title->SetText(ss.str());

    UITextBoxPtr lap0 = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("lap_0"));
    ss.str("");
    ss << "Lap: " << firstPlayerManager_->GetCurrentLapNumber() << " / " << firstPlayerManager_->GetTotalNumberOfLaps();
    lap0->SetText(ss.str());
    if (secondPlayerVehicle_ != nullptr) {
        UITextBoxPtr lap0 = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("lap_1"));
        ss.str("");
        ss << "Lap: " << secondPlayerManager_->GetCurrentLapNumber() << " / " << secondPlayerManager_->GetTotalNumberOfLaps();
        lap0->SetText(ss.str());
    }
}

void Gameplay::PrepareUIForPauseState() {
    UIBoxPtr back = userInterface_->CreateBox("background", sf::FloatRect(0.5, 0.5, 1, 1));
    back->SetBackgroundColor(sf::Color(0, 0, 0, 80));
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "PAUSE", 30,
                                                       sf::FloatRect(0.5, 0.5, 1, 0.1));
    SetTitleStyle(title);
}

void Gameplay::PrepareHUD() {
    userInterface_->DeleteElementByName("title");
    userInterface_->DeleteElementByName("background");
    UITextBoxPtr title = userInterface_->CreateTextBox("time", "", 30,
                                                       sf::FloatRect(0.5, 0.075, 0.2, 0.1));
    SetTitleStyle(title);
    UITextBoxPtr lap0 = userInterface_->CreateTextBox("lap_0", "?", 20,
                                                       sf::FloatRect(0.1, 0.075, 0.2, 0.06));
    SetTitleStyle(lap0);
    if (secondPlayerVehicle_ != nullptr) {
        UITextBoxPtr lap1 = userInterface_->CreateTextBox("lap_1", "?", 20,
                                                          sf::FloatRect(0.9, 0.075, 0.2, 0.06));
        SetTitleStyle(lap1);
    }
}

void Gameplay::UpdateUIInEndState() {

}

void Gameplay::PrepareUIForEndState() {
    userInterface_->DeleteElementByName("time");
    userInterface_->DeleteElementByName("lap_0");
    if (secondPlayerVehicle_ != nullptr)
        userInterface_->DeleteElementByName("lap_1");

    UITextBoxPtr title = userInterface_->CreateTextBox("finish", "", 60,
                                                       sf::FloatRect(0.5, 0.5, 1, 0.2));
    SetTitleStyle(title);
    std::stringstream ss;
    ss << "Player " << winnerName_ << " won!" ;
    title->SetText(ss.str());
}

void Gameplay::UpdateGame() {
    float dt = 1.f / 60.f;
    globalTime_ += dt;
    world_->Step(dt, 8, 6);
    if (firstPlayerVehicle_ != nullptr) {
        firstPlayerVehicle_->Update(dt);
        firstPlayerManager_->Update(dt);
        if (firstPlayerManager_->GetCurrentLapNumber() > laps_) {
            isOver_ = true;
            winnerName_ = firstPlayerName_;
        }
    }
    if (secondPlayerVehicle_ != nullptr) {
        secondPlayerVehicle_->Update(dt);
        secondPlayerManager_->Update(dt);
        if (secondPlayerManager_->GetCurrentLapNumber() > laps_) {
            isOver_ = true;
            winnerName_ = secondPlayerName_;
        }
    }
    UpdateHUD();
    if (isOver_) {
        gameState_ = GAMEPLAY_STATE_END;
        PrepareUIForEndState();
    }
}

void Gameplay::HandleKeyInPauseState(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        ExitGame();
    } else if (event.code == sf::Keyboard::Space) {
        gameState_ = GAMEPLAY_STATE_RUNNING;
        PrepareHUD();
    }
}

void Gameplay::HandleKeyInGameState(sf::Event::KeyEvent event, bool state) {
    if (event.code == sf::Keyboard::Escape) {
        gameState_ = GAMEPLAY_STATE_PAUSE;
        PrepareUIForPauseState();
    } else {
        if (firstPlayerVehicle_ != nullptr)
            HandleKeyFirstPlayer(event, state);
        if (secondPlayerVehicle_ != nullptr)
            HandleKeySecondPlayer(event, state);
    }
}

void Gameplay::HandleKeyInPrepareState(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        ExitGame();
    }
}

void Gameplay::HandleKeyInEndState(sf::Event::KeyEvent event) {
    if (event.code == sf::Keyboard::Escape) {
        ExitGame();
    }
}

void Gameplay::HandleKeyFirstPlayer(sf::Event::KeyEvent event, bool state) {
    float ref;
    float scr;
    switch (event.code) {
        case sf::Keyboard::Up:
            firstPlayerVehicle_->Accelerate(state);
            break;
        case sf::Keyboard::Down:
            firstPlayerVehicle_->Reverse(state);
            break;
        case sf::Keyboard::Left:
            firstPlayerVehicle_->TurnLeft(state);
            break;
        case sf::Keyboard::Right:
            firstPlayerVehicle_->TurnRight(state);
            break;
        case sf::Keyboard::PageDown:
            ref = scene_->GetCamera(0)->GetReferenceHeight();
            scr = scene_->GetCamera(0)->GetScreenFraction();
            scene_->GetCamera(0)->ChangeView(ref + 1, scr);
            break;
        case sf::Keyboard::PageUp:
            ref = scene_->GetCamera(0)->GetReferenceHeight();
            scr = scene_->GetCamera(0)->GetScreenFraction();
            scene_->GetCamera(0)->ChangeView(ref - 1, scr);
            break;
        default:
            break;
    }
}

void Gameplay::HandleKeySecondPlayer(sf::Event::KeyEvent event, bool state) {
    float ref;
    float scr;
    switch (event.code) {
        case sf::Keyboard::W:
            secondPlayerVehicle_->Accelerate(state);
            break;
        case sf::Keyboard::S:
            secondPlayerVehicle_->Reverse(state);
            break;
        case sf::Keyboard::A:
            secondPlayerVehicle_->TurnLeft(state);
            break;
        case sf::Keyboard::D:
            secondPlayerVehicle_->TurnRight(state);
            break;
        case sf::Keyboard::F1:
            ref = scene_->GetCamera(1)->GetReferenceHeight();
            scr = scene_->GetCamera(1)->GetScreenFraction();
            scene_->GetCamera(1)->ChangeView(ref + 1, scr);
            break;
        case sf::Keyboard::F2:
            ref = scene_->GetCamera(1)->GetReferenceHeight();
            scr = scene_->GetCamera(1)->GetScreenFraction();
            scene_->GetCamera(1)->ChangeView(ref - 1, scr);
            break;
        default:
            break;
    }
}

void Gameplay::SetTitleStyle(UITextBoxPtr textBox) {
    textBox->SetTextColor(sf::Color::White);
    textBox->SetTextColorHover(sf::Color::White);
    textBox->SetBackgroundColor(sf::Color(0x2B405Bef));
    textBox->SetBackgroundColorHover(sf::Color(0x2B405Bef));
    textBox->SetOutlineColor(sf::Color(0xE1F0FFff));
    textBox->SetOutlineColorHover(sf::Color(0xE1F0FFff));
    textBox->SetOutlineThickness(1.f);
}

void Gameplay::PrepareSecondPlayer() {
    VehicleSetupT setup;
    setup.steeringAngleMax = 20;
    setup.steeringAngleSpeed = 45;
    setup.aerodynamicFriction = 0.01;
    setup.brakesType = BRAKES_REAR;
    setup.enginePowerMax = 100000;
    setup.massBalance = 0.5; // Equal load on front and rear wheels
    setup.transmissionType = TRANSMISSION_FRONT;
    setup.vehicleMass = 300;
    /* ---------------------------------------------------------------- TESTS ---- */

    StartPositionT start = map_->GetStartPosition(1);
    secondPlayerVehicle_ = objectManager_->CreateVehicle(1, RealVec(start.x, start.y), start.rot, setup, map_);
    std::vector<CheckPointPtr> checkpoints;
    for (auto el : map_->GetCheckpoints()) {
        checkpoints.push_back(
                objectManager_->CreateCheckpoint(1, RealVec(el.x, el.y, map_->GetPixMetersScale()), el.rot));
    }
    secondPlayerManager_ = std::make_shared<CheckPointManager>(secondPlayerVehicle_, checkpoints, laps_);
    scene_->AddObject(secondPlayerVehicle_);
    scene_->AddCamera(1, 40, 0.3);
}

void Gameplay::PrepareFirstPlayer() {
/* ---------------------------------------------------------------- TESTS ---- */
    VehicleSetupT setup;
    setup.steeringAngleMax = 20;
    setup.steeringAngleSpeed = 45;
    setup.aerodynamicFriction = 0.01;
    setup.brakesType = BRAKES_FRONT;
    setup.enginePowerMax = 100000;
    setup.massBalance = 0.45; // higher load on front wheels
    setup.transmissionType = TRANSMISSION_REAR;
    setup.vehicleMass = 300;
    /* ---------------------------------------------------------------- TESTS ---- */

    StartPositionT start = map_->GetStartPosition(0);
    firstPlayerVehicle_ = objectManager_->CreateVehicle(0, RealVec(start.x, start.y), start.rot, setup, map_);
    std::vector<CheckPointPtr> checkpoints;
    for (auto el : map_->GetCheckpoints()) {
        checkpoints.push_back(
                objectManager_->CreateCheckpoint(0, RealVec(el.x, el.y, map_->GetPixMetersScale()), el.rot));
    }
    firstPlayerManager_ = std::make_shared<CheckPointManager>(firstPlayerVehicle_, checkpoints, laps_);
    scene_->AddObject(firstPlayerVehicle_);
    scene_->AddCamera(0, 40, 0.3);

}
