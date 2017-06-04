#include <Gameplay.h>

#include <ActivityManager.h>
#include <CheckPointManager.h>


Gameplay::Gameplay(const std::string &mapName, int laps) :
        Activity("race"),
        laps_(laps),
        mapName_(mapName),
        isOver_(false),
        contactListener_(std::make_shared<ContactListener>()) {
    keyMap_[FIRST_PLAYER] = {
            {sf::Keyboard::Up, ACCELERATE},
            {sf::Keyboard::Down, REVERSE},
            {sf::Keyboard::Left, TURN_LEFT},
            {sf::Keyboard::Right, TURN_RIGHT},
            {sf::Keyboard::PageDown, SIZE_DOWN},
            {sf::Keyboard::PageUp, SIZE_UP}};
    keyMap_[SECOND_PLAYER] = {
            {sf::Keyboard::W, ACCELERATE},
            {sf::Keyboard::S, REVERSE},
            {sf::Keyboard::A, TURN_LEFT},
            {sf::Keyboard::D, TURN_RIGHT},
            {sf::Keyboard::F1, SIZE_DOWN},
            {sf::Keyboard::F2, SIZE_UP}};
}

void Gameplay::Init() {
    world_ = new b2World(b2Vec2(0, 0));
    objectManager_ = std::make_shared<ObjectManager>(activityManager_.lock()->GetTextureManager(), world_);
    mapManager_ = std::make_shared<MapManager>(activityManager_.lock()->GetTextureManager(), objectManager_);
    map_ = mapManager_->CreateMap(mapName_);
    scene_ = std::make_shared<Scene>(map_);
    world_->SetContactListener(contactListener_.get());

    if (player_[FIRST_PLAYER] == nullptr) {
        std::cerr << "One player at least required!" << std::endl;
        ExitGame();
    }
    PreparePlayer(FIRST_PLAYER);
    if (player_[SECOND_PLAYER] != nullptr) {
        PreparePlayer(SECOND_PLAYER);
    }
    world_->Step(1.f / 60.f, 8, 6); // Init step
    gameState_ = GAMEPLAY_STATE_PREPARE;
    globalTime_ = 0.f;
    PrepareUIForPrepareState();
}

void Gameplay::Run() {
    Update();
    Render();
}

void Gameplay::End() {
    free(world_);
}

void Gameplay::EventAction(Event event) {
    if (event.GetType() == SFML_EVENT) {
        if (event.GetSFMLEvent().type == sf::Event::KeyPressed) {
            HandleKey(event.GetSFMLEvent().key, true);
        } else if (event.GetSFMLEvent().type == sf::Event::KeyReleased) {
            HandleKey(event.GetSFMLEvent().key, false);
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

void Gameplay::SetSecondPlayer(PlayerPtr player) {
    player_[SECOND_PLAYER] = player;
}

void Gameplay::SetFirstPlayer(PlayerPtr player) {
    player_[FIRST_PLAYER] = player;
}

void Gameplay::ExitGame() {
    activityManager_.lock()->RemoveActivity("race");
    activityManager_.lock()->SetAsActive("main_menu");
}

void Gameplay::SaveTimes() {
    std::string mapName = map_->GetMapName();
    float firstPlayerTime = playerCheckpoints_[FIRST_PLAYER]->GetTimeManager()
            ->GetBestLapTime();
    player_[FIRST_PLAYER]->setTime(mapName, firstPlayerTime);
    if (player_[SECOND_PLAYER] != nullptr) {
        float secondPlayerTime = playerCheckpoints_[SECOND_PLAYER]->GetTimeManager()
                ->GetBestLapTime();
        player_[SECOND_PLAYER]->setTime(mapName, secondPlayerTime);
    }
}

void Gameplay::Render() {
    /* Rendering */
    RendererPtr renderer = activityManager_.lock()->GetRenderer();
    renderer->Clear();
    if (playerVehicle_[SECOND_PLAYER] == nullptr)
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
    ss << "Start in " << (int) ceil(preparationTimeInSeconds - globalTime_)
       << " seconds!";
    title->SetText(ss.str());
}

void Gameplay::UpdateUIInPauseState() {}

void Gameplay::PrepareUIForPrepareState() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
    back->SetBackgroundColor(sf::Color(0, 0, 0, 80));
    UITextBoxPtr title = userInterface_->CreateTextBox("title", "Prepare to race!", 60,
                                                       sf::FloatRect(0.5, 0.075, 1, 0.2));
    SetTitleStyle(title);
}

void Gameplay::UpdateHUD() {
    UITextBoxPtr title = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("time"));
    std::stringstream ss;
    ss << (int) (globalTime_ / 60.) << ":" << ((int) globalTime_) % 60 << ":"
       << (int) (globalTime_ * 100) % 100;
    title->SetText(ss.str());

    UITextBoxPtr lap0 = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("lap_0"));
    ss.str("");
    ss << "Lap: " << playerCheckpoints_[0]->GetCurrentLapNumber() << " / "
       << playerCheckpoints_[0]->GetTotalNumberOfLaps();
    lap0->SetText(ss.str());

    minimap_[FIRST_PLAYER]->Update(playerVehicle_[FIRST_PLAYER]->GetPosition(),
                                   playerCheckpoints_[FIRST_PLAYER]->GetNextCheckPointPosition());

    if (playerVehicle_[SECOND_PLAYER] != nullptr) {
        UITextBoxPtr lap1 = std::dynamic_pointer_cast<UITextBox>(userInterface_->GetElementByName("lap_1"));
        ss.str("");
        ss << "Lap: "
           << playerCheckpoints_[SECOND_PLAYER]->GetCurrentLapNumber() << " / "
                   ""
           << playerCheckpoints_[SECOND_PLAYER]->GetTotalNumberOfLaps();
        lap1->SetText(ss.str());

        minimap_[SECOND_PLAYER]->Update(playerVehicle_[SECOND_PLAYER]->GetPosition(),
                                        playerCheckpoints_[SECOND_PLAYER]->GetNextCheckPointPosition());
    }
}

void Gameplay::PrepareUIForPauseState() {
    UIBoxPtr back = userInterface_->CreateBox("background", centeredFullScreen);
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
    sf::FloatRect minimapRect(0.9, 0.85, 0.16, 0.16);
    TexturePtr minimapTexture = map_->GetMinimapTexture();
    if (playerVehicle_[SECOND_PLAYER] != nullptr) {
        UITextBoxPtr lap1 = userInterface_->CreateTextBox("lap_1", "?", 20,
                                                          sf::FloatRect(0.9, 0.075, 0.2, 0.06));
        SetTitleStyle(lap1);
        minimap_[SECOND_PLAYER] = userInterface_->CreateMinimap(
                "minimap_1", minimapRect, map_->GetSize(), minimapTexture);
        minimapRect = sf::FloatRect(0.4, 0.85, 0.16, 0.16);
    }
    minimap_[FIRST_PLAYER] = userInterface_->CreateMinimap(
            "minimap_0", minimapRect, map_->GetSize(), minimapTexture);
    for (auto minimap : minimap_) {
        if (minimap != nullptr) {
            minimap->SetBackgroundTexture(map_->GetMapName() + "_mini");
        }
    }
}

void Gameplay::UpdateUIInEndState() {}

void Gameplay::PrepareUIForEndState() {
    userInterface_->DeleteElementByName("time");
    userInterface_->DeleteElementByName("lap_0");
    if (playerVehicle_[1] != nullptr)
        userInterface_->DeleteElementByName("lap_1");

    UITextBoxPtr title = userInterface_->CreateTextBox("finish", "", 60,
                                                       sf::FloatRect(0.5, 0.5, 1, 0.2));
    SetTitleStyle(title);
    std::stringstream ss;
    ss << "Player " << winnerName_ << " won!";
    title->SetText(ss.str());
}

void Gameplay::UpdateGame() {
    float dt = 1.f / 60.f;
    globalTime_ += dt;
    world_->Step(dt, 8, 6);
    UpdatePlayer(FIRST_PLAYER, dt);
    UpdatePlayer(SECOND_PLAYER, dt);
    UpdateHUD();
    if (isOver_) {
        SaveTimes();
        gameState_ = GAMEPLAY_STATE_END;
        PrepareUIForEndState();
    }
}

void Gameplay::UpdatePlayer(int id, float dt) {
    if (playerVehicle_[id] != nullptr) {
        playerVehicle_[id]->Update(dt);
        playerCheckpoints_[id]->Update(dt);
        if (playerCheckpoints_[id]->GetCurrentLapNumber() > laps_) {
            isOver_ = true;
            winnerName_ = player_[id]->GetName();
        }
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
        for (int id = 0; id < MAX_PLAYER; id++) {
            if (playerVehicle_[id] != nullptr)
                HandleKeyPlayerAction(id, event, state);
        }
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

void Gameplay::HandleKeyPlayerAction(unsigned id, sf::Event::KeyEvent event, bool state) {
    float ref;
    float scr;
    auto key = keyMap_[id].find(event.code);
    switch (key->second) {
        case ACCELERATE:
            playerVehicle_[id]->Accelerate(state);
            break;
        case REVERSE:
            playerVehicle_[id]->Reverse(state);
            break;
        case TURN_LEFT:
            playerVehicle_[id]->TurnLeft(state);
            break;
        case TURN_RIGHT:
            playerVehicle_[id]->TurnRight(state);
            break;
        case SIZE_DOWN:
            ref = scene_->GetCamera(id)->GetReferenceHeight();
            scr = scene_->GetCamera(id)->GetScreenFraction();
            scene_->GetCamera(id)->ChangeView(ref + 1, scr);
            break;
        case SIZE_UP:
            ref = scene_->GetCamera(id)->GetReferenceHeight();
            scr = scene_->GetCamera(id)->GetScreenFraction();
            scene_->GetCamera(id)->ChangeView(ref - 1, scr);
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

void Gameplay::PreparePlayer(int id) {
    auto configuration = player_[id]->GetCarConfiguration();
    auto start = map_->GetStartPosition(id);
    auto startPos = RealVec(start.x, start.y);
    playerVehicle_[id] = objectManager_->CreateVehicle(id, startPos, start.rot, {}, map_, configuration);
    std::vector<CheckPointPtr> checkpoints;
    for (auto el : map_->GetCheckpoints()) {
        auto pos = RealVec(el.x, el.y, map_->GetPixMetersScale());
        auto playerCheckpoint = objectManager_->CreateCheckpoint(id, pos , el.rot);
        checkpoints.push_back(playerCheckpoint);
    }
    playerCheckpoints_[id] = std::make_shared<CheckPointManager>(playerVehicle_[id], checkpoints, laps_);
    scene_->AddObject(playerVehicle_[id]);
    scene_->AddCamera((unsigned) id, 40, 0.3);
}
