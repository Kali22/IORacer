/**
 *  @file
 *  @ingroup hud
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <Tools/HUD.h>
#include <Entity/TimeIndicator.h>
#include <Entity/IntegerIndicator.h>

HUD::HUD(VehiclePtr vehicle, MapPtr map)
        : vehicle_(vehicle), map_(map) {
    hudView_.setSize(1200, 800);
    hudView_.setCenter(550, 350);
    hudView_.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    showDebug_ = false;
}

HUD::~HUD() {}

void HUD::Initialize(VehiclePtr vehicle, CheckPointManagerPtr checkPointManager) {
    vehicle_ = vehicle;
    checkPointManager_ = checkPointManager;

    CreateSectorLapContainer();
    CreateLapTimeContainer();
    CreateSectorTimeContainer();
    CreateNotifyContainer();
}

void HUD::Update() {
    if (vehicle_ == nullptr || checkPointManager_ == nullptr) {
        return;
    }

    for (auto el : containers_) {
        el->Update();
    }

    if (checkPointManager_->NewLapBeginNotify()) {
        lapFinishIndicator_->Show();
    } else {
        lapFinishIndicator_->Hide();
    }

    if (checkPointManager_->NewSectorBeginNotify()) {
        sectorFinishIndicator_->Show();
    } else {
        sectorFinishIndicator_->Hide();
    }
}

void HUD::Draw(sf::RenderWindow *window) const {
    window->setView(hudView_);

    sf::Vector2u windowSize = window->getSize();
    sf::Sprite &minimap = map_->GetMinimap();
    minimap.setPosition(windowSize.x - 360.f, windowSize.y - 250.f);
    minimap.setScale(0.39, 0.39);
    window->draw(minimap);

    float beginX = windowSize.x - 360.f;
    float beginY = windowSize.y - 250.f;
    sf::Vector2f checkpointPosition = checkPointManager_->GetNextCheckPointPosition();
    sf::Vector2f vehiclePosition = vehicle_->GetPosition();
    sf::Vector2f mapSize = map_->GetMapSize();
    float posX = vehiclePosition.x / mapSize.x * 290;
    float posY = vehiclePosition.y / mapSize.y * 160;
    checkpointPosition.x *= 290 / mapSize.x;
    checkpointPosition.y *= 160 / mapSize.y;

    sf::CircleShape vehiclePoint(5);
    sf::CircleShape checkpointPoint(5);
    vehiclePoint.setFillColor(sf::Color(255, 50, 0, 250));
    vehiclePoint.setOutlineColor(sf::Color(0, 0, 0, 150));
    vehiclePoint.setPosition(beginX + posX, beginY + posY);
    checkpointPoint.setFillColor(sf::Color(0, 250, 200, 250));
    checkpointPoint.setOutlineColor(sf::Color(0, 0, 0, 150));
    checkpointPoint.setPosition(beginX + checkpointPosition.x, beginY + checkpointPosition.y);
    window->draw(checkpointPoint);
    window->draw(vehiclePoint);

    for (auto el : containers_) {
        if (el != nullptr)
            el->Draw(window);
    }
    window->setView(window->getDefaultView());
}

void HUD::DebugDisplay(bool option) {
    showDebug_ = option;
}

void HUD::DebugDisplayToggle() {
    DebugDisplay(!showDebug_);
}

void HUD::CreateSectorLapContainer() {
    TextPtr text;
    ContainerPtr container;
    IntegerIndicatorPtr indicator;
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    int laps = checkPointManager_->GetTotalNumberOfLaps();
    int sectors = checkPointManager_->GetTotalNumberOfSectors();

    //-------- Create sector & lap counter container
    container = std::make_shared<Container>(sf::FloatRect(0, 400, 174, 67));
    // Create sector counter label
    text = std::make_shared<Text>("Sector:", "impact", sf::FloatRect(2.5, 2.5, 75, 30), 20, TEXT_RIGHT);
    container->AddMovable(text);
    // Create lap counter label
    text = std::make_shared<Text>("Lap:", "impact", text->GetSameFrameBelow(2.f), 20, TEXT_RIGHT);
    container->AddMovable(text);

    text = std::make_shared<Text>((std::string("of ") + std::to_string(sectors)).c_str(), "impact",
                                  sf::FloatRect(100.5, 2.5, 60, 30), 20, TEXT_LEFT);
    container->AddMovable(text);
    text = std::make_shared<Text>((std::string("of ") + std::to_string(laps)).c_str(), "impact",
                                  sf::FloatRect(100.5, 34.5, 60, 30), 20, TEXT_LEFT);
    container->AddMovable(text);

    // Current sector indicator
    indicator = std::make_shared<IntegerIndicator>(timeManager->GetCurrentSectorNumber(),
                                                   sf::FloatRect(79.5, 2.5, 20, 30), TEXT_RIGHT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);
    // Current lap indicator
    indicator = std::make_shared<IntegerIndicator>(timeManager->GetCurrentLapNumber(),
                                                   sf::FloatRect(79.5, 34.5, 20, 30), TEXT_RIGHT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);

    container->FrameOn();
    containers_.push_back(container);
}

void HUD::CreateLapTimeContainer() {
    TextPtr text;
    TimeIndicatorPtr indicator;
    ContainerPtr containter;
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    //-------- Create lap time counter containter
    containter = std::make_shared<Container>(sf::FloatRect(0, 510, 207, 167));
    // Create box label
    text = std::make_shared<Text>("LAP TIME", "impact", sf::FloatRect(2.5, 2.5, 202, 30), 20, TEXT_CENTER);
    containter->AddMovable(text);
    // Create current lap time label
    text = std::make_shared<Text>("Current:", "impact", sf::FloatRect(2.5, 34.5, 100, 30), 20, TEXT_RIGHT);
    containter->AddMovable(text);
    // Create last lap time label
    text = std::make_shared<Text>("Last:", "impact", text->GetSameFrameBelow(2.f), 20, TEXT_RIGHT);
    containter->AddMovable(text);
    // Create best lap time label
    text = std::make_shared<Text>("Best:", "impact", text->GetSameFrameBelow(2.f), 20, TEXT_RIGHT);
    containter->AddMovable(text);
    // Create combined lap time label
    text = std::make_shared<Text>("Combined:", "impact", text->GetSameFrameBelow(2.f), 20, TEXT_RIGHT);
    containter->AddMovable(text);

    // Create combined lap time data
    indicator = std::make_shared<TimeIndicator>(timeManager->GetCombinedBestLapTime(), text->GetSameFrameRight(2.f),
                                                TEXT_LEFT, "impact", 20);
    containter->AddMovable(indicator);
    containter->AddUpdatable(indicator);
    // Create best lap time data
    indicator = std::make_shared<TimeIndicator>(timeManager->GetBestLapTime(), indicator->GetSameFrameAbove(2.f),
                                                TEXT_LEFT, "impact", 20);
    containter->AddMovable(indicator);
    containter->AddUpdatable(indicator);
    // Create last lap time data
    indicator = std::make_shared<TimeIndicator>(timeManager->GetLastLapTime(), indicator->GetSameFrameAbove(2.f),
                                                TEXT_LEFT, "impact", 20);
    containter->AddMovable(indicator);
    containter->AddUpdatable(indicator);
    // Create current lap time data
    indicator = std::make_shared<TimeIndicator>(timeManager->GetCurrentLapTime(), indicator->GetSameFrameAbove(2.f),
                                                TEXT_LEFT, "impact", 20);
    containter->AddMovable(indicator);
    containter->AddUpdatable(indicator);

    containter->FrameOn();
    containers_.push_back(containter);
}

void HUD::CreateSectorTimeContainer() {
    TextPtr text;
    TimeIndicatorPtr indicator;
    ContainerPtr container;
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    //-------- Create lap time counter container
    container = std::make_shared<Container>(sf::FloatRect(220, 510, 207, 167));
    // Create box label
    text = std::make_shared<Text>("SECTOR TIME", "impact", sf::FloatRect(2.5, 2.5, 202, 30), 20, TEXT_CENTER);
    container->AddMovable(text);
    // Create current sector time label
    text = std::make_shared<Text>("Current:", "impact", sf::FloatRect(2.5, 34.5, 100, 30), 20, TEXT_RIGHT);
    container->AddMovable(text);
    // Create last sector time label
    text = std::make_shared<Text>("Last:", "impact", text->GetSameFrameBelow(2.f), 20, TEXT_RIGHT);
    container->AddMovable(text);
    // Create best sector time label
    text = std::make_shared<Text>("Best:", "impact", text->GetSameFrameBelow(2.f), 20, TEXT_RIGHT);
    container->AddMovable(text);

    // Create best sector time indicator
    indicator = std::make_shared<TimeIndicator>(timeManager->GetBestSectorTime(), text->GetSameFrameRight(2.f),
                                                TEXT_LEFT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);
    // Create last time in current sector indicator
    indicator = std::make_shared<TimeIndicator>(timeManager->GetLastSectorTime(), indicator->GetSameFrameAbove(2.f),
                                                TEXT_LEFT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);
    // Create current sector time indicator
    indicator = std::make_shared<TimeIndicator>(timeManager->GetCurrentSectorTime(), indicator->GetSameFrameAbove(2.f),
                                                TEXT_LEFT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);

    container->FrameOn();
    containers_.push_back(container);
}

void HUD::CreateNotifyContainer() {
    TimeIndicatorPtr indicator;
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    //-------- Create finish lap indicator
    lapFinishIndicator_ = std::make_shared<Container>(sf::FloatRect(400, 10, 300, 50));
    indicator = std::make_shared<TimeIndicator>(timeManager->GetLastLapTime(), sf::FloatRect(0, 0, 300, 50),
                                                TEXT_CENTER, "impact", 40);
    lapFinishIndicator_->AddMovable(indicator);
    lapFinishIndicator_->AddUpdatable(indicator);
    lapFinishIndicator_->FrameOn();
    lapFinishIndicator_->Hide();
    containers_.push_back(lapFinishIndicator_);

    //-------- Create finish sector indicator
    sectorFinishIndicator_ = std::make_shared<Container>(sf::FloatRect(475, 65, 150, 20));
    indicator = std::make_shared<TimeIndicator>(timeManager->GetPreviousSectorTime(), sf::FloatRect(0, 0, 150, 20),
                                                TEXT_CENTER, "impact", 20);
    sectorFinishIndicator_->AddMovable(indicator);
    sectorFinishIndicator_->AddUpdatable(indicator);
    sectorFinishIndicator_->FrameOn();
    sectorFinishIndicator_->Hide();
    containers_.push_back(sectorFinishIndicator_);
}
