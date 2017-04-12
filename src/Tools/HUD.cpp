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
          lapLabels_("y", "impact", sf::Vector2f(0, 550), 20),
          lapData_("y", "impact", sf::Vector2f(120, 550), 20),
          timeLabels_("y", "impact", sf::Vector2f(0, 625), 20),
          timeData_("y", "impact", sf::Vector2f(85, 625), 20),
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
    ss << "Checkpoint:\n";
    ss << "  \t\t\t\tLap:\n";
    lapLabels_.SetText(ss.str());

    ss.str("");
    ss << "\t\t\tTIME\n";
    ss << "Current:\n";
    ss << "\t    Last:\n";
    ss << "\t    Best:";
    timeLabels_.SetText(ss.str());
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
    int currentCheckPoint = checkPointManager_->GetCurrentCheckPointNumber();
    int totalCheckPoints = checkPointManager_->GetTotalNumberOfCheckPoints();
    int currentLap = checkPointManager_->GetCurrentLap();
    int totalLaps = checkPointManager_->GetTotalLaps();
    ss << currentCheckPoint << " / " << totalCheckPoints << "\n";
    ss << currentLap << " / " << totalLaps;
    lapData_.SetText(ss.str());

    ss.str("");
    float currentLapTime = checkPointManager_->GetCurrentLapTime();
    float latLapTime = checkPointManager_->GetLastLapTime();
    float bestLapTime = checkPointManager_->GetBestLapTime();
    ss << "\n";
    ss << (int) (currentLapTime / 60.) << ":" << (((int) currentLapTime) % 60) << "." << (int) (currentLapTime * 1000.0f) % 1000 << "\n";
    /// @TODO CheckPointManager - get last lap time (float ?)
    ss << 1 << ":" << 50 << "." << 324 << "\n";
    /// @TODO CheckPointManager - get best lap time (float ?)
    ss << 1 << ":" << 50 << "." << 324 << "\n";
    timeData_.SetText(ss.str());
}

void HUD::Draw(sf::RenderWindow *window) const {
    // Draw data
    window->setView(hudView_);
    if (showDebug_) {
        PrintBackBox(window, -10.f, -20.f, 200, 500);
        debugData_.Draw(window);
    }
    PrintBackBox(window, -10.f, 600.f, 200, 120);
    PrintBackBox(window, -10.f, 530.f, 200, 56);
    timeData_.Draw(window);
    timeLabels_.Draw(window);
    lapData_.Draw(window);
    lapLabels_.Draw(window);

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

