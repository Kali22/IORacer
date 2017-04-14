/**
 *  @file
 *  @ingroup hud
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 4/5/17
 */

#include <Tools/HUD.h>
#include <iomanip>

HUD::HUD(VehiclePtr vehicle, MapPtr map)
        : vehicle_(vehicle),
          debugData_("x", "impact", sf::Vector2f(0, 0), 20),
          lapLabels_("y", "impact", sf::Vector2f(0, 500), 20),
          lapData_("y", "impact", sf::Vector2f(70, 500), 20),
          lapTimeLabels_("y", "impact", sf::Vector2f(0, 598), 20),
          lapTimeData_("y", "impact", sf::Vector2f(100, 598), 20),
          sectorTimeLabels_("y", "impact", sf::Vector2f(250, 625), 20),
          sectorTimeData_("y", "impact", sf::Vector2f(330, 625), 20),
          lapFinishedIndicator_("y", "impact", sf::Vector2f(500, 100), 40),
          sectorFinishedIndicator_("y", "impact", sf::Vector2f(500, 150), 20),
          map_(map) {
    hudView_.setSize(1200, 800);
    hudView_.setCenter(550, 350);
    hudView_.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    /// @TODO showDebug_ = true temporary true at the begining...
    showDebug_ = true;
}

HUD::~HUD() {}

void HUD::Initialize(VehiclePtr vehicle, CheckPointManagerPtr checkPointManager) {
    vehicle_ = vehicle;
    checkPointManager_ = checkPointManager;

    std::stringstream ss;
    ss.str("");
    ss << "Sector:\n";
    ss << "   \tLap:\n";
    lapLabels_.SetText(ss.str());

    ss.str("");
    ss << "\t\t\tLAP TIME\n";
    ss << "     Current:\n";
    ss << "\t         Last:\n";
    ss << "\t         Best:\n";
    ss << "Combined:\n";
    lapTimeLabels_.SetText(ss.str());

    ss.str("");
    ss << "\t  SECTOR TIME\n";
    ss << "Current:\n";
    ss << "\t    Last:\n";
    ss << "\t    Best:";
    sectorTimeLabels_.SetText(ss.str());
}

void HUD::Update() {
    if (vehicle_ == nullptr || checkPointManager_ == nullptr) {
        return;
    }
    std::stringstream ss;

    // Get debug data if needed
    if (showDebug_) {
        sf::Vector2f mapPos = vehicle_->GetPosition();
        sf::Vector2f boxPos = vehicle_->GetBoxPosition();
        ss << std::fixed;
        ss << std::setprecision(3);
        ss << "--- SFML ---\n";
        ss << "X[px]: " << mapPos.x << "\n";
        ss << "Y[px]: " << mapPos.y << "\n";
        ss << "[deg]: " << vehicle_->GetAngle() << "\n\n";

        ss << "--- Box 2D ---\n";
        ss << "X[m]: " << boxPos.x << "\n";
        ss << "Y[m]: " << boxPos.y << "\n";
        ss << "[rad]: " << vehicle_->GetBoxAngle() << "\n";
        ss << "vel[m/s]: " << vehicle_->GetSpeed() << "\n";
        /// @todo vehicle - get actuall steering angle
        ss << "steer[deg]: " << 0.000 << "\n";
        /// @todo vehicle - get lock angle
        ss << "lock[deg]: " << 0.000 << "\n\n";


        ss << "--- Tires ---\n";
        ss << "FL mod: " << vehicle_->GetTireModifier(0, *map_) << "\n";
        ss << "FR mod: " << vehicle_->GetTireModifier(1, *map_) << "\n";
        ss << "BL mod: " << vehicle_->GetTireModifier(3, *map_) << "\n";
        ss << "BR mod: " << vehicle_->GetTireModifier(2, *map_) << "\n";
        debugData_.SetText(ss.str());
    }

    // Prepare lap and time data
    ss.str("");
    int currentCheckPoint = checkPointManager_->GetCurrentSectorNumber();
    int totalCheckPoints = checkPointManager_->GetTotalNumberOfSectors();
    int currentLap = checkPointManager_->GetCurrentLap();
    int totalLaps = checkPointManager_->GetTotalLaps();
    ss << currentCheckPoint << " / " << totalCheckPoints << "\n";
    ss << currentLap << " / " << totalLaps;
    lapData_.SetText(ss.str());


    float currentLapTime = checkPointManager_->GetCurrentLapTime();
    float lastLapTime = checkPointManager_->GetLastLapTime();
    float bestLapTime = checkPointManager_->GetBestLapTime();
    float currentSectorTime = checkPointManager_->GetCurrentSectorTime();
    float lastSectorTime = checkPointManager_->GetLastSectorTime();
    float bestSectorTime = checkPointManager_->GetBestSectorTime();
    float combineTime = checkPointManager_->GetCombinedBestTime();
    ss.str("");
    ss << "\n";
    ss << (int) (currentLapTime / 60.) << ":" << (((int) currentLapTime) % 60) << "."
       << (int) (currentLapTime * 1000.0f) % 1000 << "\n";
    ss << (int) (lastLapTime / 60.) << ":" << (((int) lastLapTime) % 60) << "." << (int) (lastLapTime * 1000.0f) % 1000
       << "\n";
    ss << (int) (bestLapTime / 60.) << ":" << (((int) bestLapTime) % 60) << "." << (int) (bestLapTime * 1000.0f) % 1000
       << " / " << checkPointManager_->GetBestLapNumber() << "\n";
    ss << (int) (combineTime / 60.) << ":" << (((int) combineTime) % 60) << "." << (int) (combineTime * 1000.0f) % 1000
       << "\n";
    lapTimeData_.SetText(ss.str());

    ss.str("");
    ss << "\n";
    ss << (int) (currentSectorTime / 60.) << ":" << (((int) currentSectorTime) % 60) << "."
       << (int) (currentSectorTime * 1000.0f) % 1000 << "\n";
    ss << (int) (lastSectorTime / 60.) << ":" << (((int) lastSectorTime) % 60) << "." << (int) (lastSectorTime * 1000.0f) % 1000
       << "\n";
    ss << (int) (bestSectorTime / 60.) << ":" << (((int) bestSectorTime) % 60) << "." << (int) (bestSectorTime * 1000.0f) % 1000
       << " / " << checkPointManager_->GetBestSectorLapNumber() << "\n";
    sectorTimeData_.SetText(ss.str());

    if (checkPointManager_->IsLapFinished()) {
        ss.str("");
        ss << (int) (lastLapTime / 60.) << ":" << (((int) lastLapTime) % 60) << "."
           << (int) (lastLapTime * 1000.0f) % 1000 << "\n";
        lapFinishedIndicator_.SetText(ss.str());
    }

    if (checkPointManager_->IsSectorFinished()) {
        ss.str("");
        float previousSectorTime = checkPointManager_->GetPreviousSectorTime();
        ss << (int) (previousSectorTime / 60.) << ":" << (((int) previousSectorTime) % 60) << "."
           << (int) (previousSectorTime * 1000.0f) % 1000 << "\n";
        sectorFinishedIndicator_.SetText(ss.str());
    }
}

void HUD::Draw(sf::RenderWindow *window) const {
    // Draw data
    window->setView(hudView_);
    if (showDebug_) {
        PrintBackBox(window, -10.f, -20.f, 200, 450);
        debugData_.Draw(window);
    }
    PrintBackBox(window, -10.f, 570.f, 230, 150);
    PrintBackBox(window, -10.f, 480.f, 200, 56);
    PrintBackBox(window, 230.f, 600.f, 200, 120);
    lapTimeData_.Draw(window);
    lapTimeLabels_.Draw(window);
    lapData_.Draw(window);
    lapLabels_.Draw(window);
    sectorTimeData_.Draw(window);
    sectorTimeLabels_.Draw(window);

    // Draw minimap
    sf::Vector2u windowSize = window->getSize();
    PrintBackBox(window, windowSize.x - 360.f, windowSize.y - 250.f, 300, 170.f);
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

    if (checkPointManager_->IsLapFinished()) {
        lapFinishedIndicator_.Draw(window);
    }

    if (checkPointManager_->IsSectorFinished()) {
        sectorFinishedIndicator_.Draw(window);
    }

    window->setView(window->getDefaultView());
}

void HUD::DebugDisplay(bool option) {
    showDebug_ = option;
}

void HUD::PrintBackBox(sf::RenderWindow *window, float posX, float posY, float sizeX, float sizeY) const {
    sf::RectangleShape back;
    back.setFillColor(sf::Color(0, 0, 0, 80));
    back.setOutlineColor(sf::Color(255, 255, 255, 100));
    back.setOutlineThickness(2.0);
    back.setOrigin(0, 0);
    back.setSize(sf::Vector2f(sizeX, sizeY));
    back.setPosition(posX, posY);
    window->draw(back);
}

void HUD::DebugDisplayToggle() {
    if (showDebug_)
        DebugDisplay(false);
    else
        DebugDisplay(true);
}

