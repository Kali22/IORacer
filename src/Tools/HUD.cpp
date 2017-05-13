/**
 *  @file
 *  @ingroup hud
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <HUD.h>
#include <TimeIndicator.h>
#include <IntegerIndicator.h>
#include <Drawable.h>

HUD::HUD(VehiclePtr vehicle, MapPtr map) : vehicle_(vehicle), map_(map) {
    hudView_.setSize(1200, 800);
    hudView_.setCenter(550, 350);
    hudView_.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    showDebug_ = false;
}

void HUD::Initialize(VehiclePtr vehicle, CheckPointManagerPtr checkPointManager) {
    vehicle_ = vehicle;
    checkPointManager_ = checkPointManager;

    CreateSectorLapContainer(sf::FloatRect(0, 450, 207, 70));
    CreateLapTimeContainer(sf::FloatRect(0, 550, 207, 167));
    CreateSectorTimeContainer(sf::FloatRect(215, 550, 207, 167));
    CreateNotifyContainer(sf::FloatRect(400, 100, 300, 50), sf::FloatRect(425, 160, 250, 50));
}

void HUD::Update() {
    if (vehicle_ == nullptr || checkPointManager_ == nullptr) {
        return;
    }

    for (auto &el : containers_) {
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

void HUD::Draw(RenderWindowPtr window) const {
    window->setView(hudView_);

    // DrawMinimap(window);

    for (auto el : containers_) {
        if (el != nullptr)
            el->Draw(window);
    }
    window->setView(window->getDefaultView());
}
/*
void HUD::DrawMinimap(sf::RenderWindow *window) const {
    sf::Vector2u windowSize = window->getSize();
    float beginX = windowSize.x - 360.f;
    float beginY = windowSize.y - 250.f;
    sf::Vector2f mapSize = map_->GetMapSize();

    DrawMinimapBackground(window, windowSize);
    DrawMinimapVehicle(window, mapSize, beginX, beginY);
    DrawMinimapCheckpoint(window, mapSize, beginX, beginY);
}

void HUD::DrawMinimapBackground(sf::RenderWindow *window, const sf::Vector2u &windowSize) const {
    sf::Sprite &minimap = map_->GetMinimap();
    minimap.setPosition(windowSize.x - 360.f, windowSize.y - 250.f);
    minimap.setScale(0.39, 0.39);
    window->draw(minimap);
}

void HUD::DrawMinimapVehicle(sf::RenderWindow *window,
                             const sf::Vector2f &mapSize,
                             float beginX, float beginY) const {
    sf::Vector2f vehiclePosition = vehicle_->GetPosition();
    float posX = vehiclePosition.x / mapSize.x * 290;
    float posY = vehiclePosition.y / mapSize.y * 160;

    sf::CircleShape vehiclePoint(5);
    vehiclePoint.setFillColor(sf::Color(255, 50, 0, 250));
    vehiclePoint.setOutlineColor(sf::Color(0, 0, 0, 150));
    vehiclePoint.setPosition(beginX + posX, beginY + posY);
    window->draw(vehiclePoint);
}

void HUD::DrawMinimapCheckpoint(sf::RenderWindow *window,
                                const sf::Vector2f &mapSize,
                                float beginX, float beginY) const {
    sf::Vector2f checkpointPosition = checkPointManager_->GetNextCheckPointPosition();
    float posX = checkpointPosition.x / mapSize.x * 290;
    float posY = checkpointPosition.y / mapSize.y * 160;

    sf::CircleShape checkpointPoint(5);
    checkpointPoint.setFillColor(sf::Color(0, 250, 200, 250));
    checkpointPoint.setOutlineColor(sf::Color(0, 0, 0, 150));
    checkpointPoint.setPosition(beginX + posX, beginY + posY);
    window->draw(checkpointPoint);
}*/

void HUD::DebugDisplay(bool option) {
    showDebug_ = option;
}

void HUD::DebugDisplayToggle() {
    DebugDisplay(!showDebug_);
}

void HUD::CreateSectorLapContainer(sf::FloatRect frame) {
    int laps = checkPointManager_->GetTotalNumberOfLaps();
    int sectors = checkPointManager_->GetTotalNumberOfSectors();
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    ContainerPtr container = std::make_shared<Container>(frame);
    AddIntegerIndicator(container, "Sector:", timeManager->GetCurrentSectorNumber(), sectors, sf::IntRect(1, 2, 0, 0));
    AddIntegerIndicator(container, "Lap:", timeManager->GetCurrentLapNumber(), laps, sf::IntRect(1, 2, 0, 1));
    container->FrameOn();
    containers_.push_back(container);
}

void HUD::CreateLapTimeContainer(sf::FloatRect frame) {
    TextPtr text;
    TimeIndicatorPtr indicator;
    ContainerPtr container;
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    container = std::make_shared<Container>(frame);
    AddContainerTitle(container, "LAP TIME");
    AddTimeIndicator(container, "Current:", timeManager->GetCurrentLapTime(), sf::IntRect(1, 5, 0, 1));
    AddTimeIndicator(container, "Last:", timeManager->GetLastLapTime(), sf::IntRect(1, 5, 0, 2));
    AddTimeIndicator(container, "Best:", timeManager->GetBestLapTime(), sf::IntRect(1, 5, 0, 3));
    AddTimeIndicator(container, "Combined:", timeManager->GetCombinedBestLapTime(), sf::IntRect(1, 5, 0, 4));
    container->FrameOn();
    containers_.push_back(container);
}

void HUD::CreateSectorTimeContainer(sf::FloatRect frame) {
    TextPtr text;
    TimeIndicatorPtr indicator;
    ContainerPtr container;
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    container = std::make_shared<Container>(frame);
    AddContainerTitle(container, "SECTOR TIME");
    AddTimeIndicator(container, "Current:", timeManager->GetCurrentSectorTime(), sf::IntRect(1, 5, 0, 1));
    AddTimeIndicator(container, "Last:", timeManager->GetLastSectorTime(), sf::IntRect(1, 5, 0, 2));
    AddTimeIndicator(container, "Best:", timeManager->GetBestSectorTime(), sf::IntRect(1, 5, 0, 3));
    container->FrameOn();
    containers_.push_back(container);
}

void HUD::CreateNotifyContainer(sf::FloatRect lapFrame, sf::FloatRect sectorFrame) {
    TimeManagerPtr timeManager = checkPointManager_->GetTimeManager();
    lapFinishIndicator_ = std::make_shared<Container>(lapFrame);
    AddTimeIndicatorWithoutTitle(lapFinishIndicator_, timeManager->GetLastLapTime(), sf::IntRect(1, 1, 0, 0), 40);
    lapFinishIndicator_->FrameOn();
    lapFinishIndicator_->Hide();
    containers_.push_back(lapFinishIndicator_);

    sectorFinishIndicator_ = std::make_shared<Container>(sectorFrame);
    AddTimeIndicatorWithoutTitle(
            sectorFinishIndicator_, timeManager->GetPreviousSectorTime(), sf::IntRect(1, 1, 0, 0), 30);
    sectorFinishIndicator_->FrameOn();
    sectorFinishIndicator_->Hide();
    containers_.push_back(sectorFinishIndicator_);
}

void HUD::AddContainerTitle(ContainerPtr container, std::string title) {
    TextPtr text;
    sf::Vector2f containerSize = container->GetSize();
    sf::FloatRect pos(2.5, 2.5, containerSize.x - 5.f, 25.f);
    text = std::make_shared<Text>(title, "impact", pos, 20, TEXT_CENTER);
    container->AddMovable(text);
}

void HUD::AddTimeIndicator(ContainerPtr container, std::string title, const float &data, sf::IntRect grid) {
    TextPtr text;
    TimeIndicatorPtr indicator;
    sf::FloatRect frame = container->GetGridElement(grid.left, grid.top, grid.width, grid.height, 2.5f);
    frame.width /= 2;
    text = std::make_shared<Text>(title, "impact", frame, 20, TEXT_RIGHT);
    container->AddMovable(text);
    frame.left += frame.width;
    indicator = std::make_shared<TimeIndicator>(data, frame, TEXT_LEFT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);
}

void HUD::AddIntegerIndicator(ContainerPtr container, std::string title, const int &data, int limit, sf::IntRect grid) {
    TextPtr text;
    IntegerIndicatorPtr indicator;
    sf::FloatRect frame = container->GetGridElement(grid.left, grid.top, grid.width, grid.height, 2.5f);
    frame.width /= 2;
    text = std::make_shared<Text>(title, "impact", frame, 20, TEXT_RIGHT);
    container->AddMovable(text);
    frame.left += frame.width;
    frame.width /= 2;
    indicator = std::make_shared<IntegerIndicator>(data, frame, TEXT_RIGHT, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);
    frame.left += frame.width;
    text = std::make_shared<Text>((std::string("of ") + std::to_string(limit)).c_str(), "impact", frame, 20, TEXT_LEFT);
    container->AddMovable(text);
}

void HUD::AddTimeIndicatorWithoutTitle(ContainerPtr container, const float &data, sf::IntRect grid, float fontSize) {
    TextPtr text;
    TimeIndicatorPtr indicator;
    sf::FloatRect frame = container->GetGridElement(grid.left, grid.top, grid.width, grid.height, 2.5f);
    indicator = std::make_shared<TimeIndicator>(data, frame, TEXT_CENTER, "impact", 20);
    container->AddMovable(indicator);
    container->AddUpdatable(indicator);
}
