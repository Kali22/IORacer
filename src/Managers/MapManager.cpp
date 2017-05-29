#include <fstream>
#include <sstream>
#include <iostream>
#include <MapManager.h>
#include <MathUtil.h>

MapManager::MapManager(TextureManagerPtr textureManager,
                       ObjectManagerPtr objectManager) :
        textureManager_(textureManager),
        objectManager_(objectManager) {
    std::ifstream file(resourcePath_ + cnfgFile_);
    std::string line;
    std::stringstream data;
    std::string mapName;
    std::string fileName;

    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        data = std::stringstream(line);
        data >> mapName >> fileName;

        maps_.emplace(mapName, fileName);
        std::cerr << "Map description loaded: [" << mapName << ", " << fileName
                  << "]\n";
    }
}

MapPtr MapManager::CreateMap(std::string mapName) {
    std::cerr << "Creating map: " << mapName << std::endl;
    std::map<std::string, std::string>::iterator it = maps_.find(mapName);
    if (it == maps_.end()) {
        return nullptr;
    }

    std::ifstream file(resourcePath_ + maps_[mapName]);
    std::string description;
    float sizeX, sizeY;

    while (getline(file, description)) {
        if (description[0] != '#') {
            break;
        }
    }
    file >> sizeX >> sizeY;

    std::string name;
    file >> name;
    TexturePtr view = textureManager_->GetTextureByName(name);

    file >> name;
    TexturePtr friction = textureManager_->GetTextureByName(name);

    file >> name;
    TexturePtr minimap = textureManager_->GetTextureByName(name);

    std::vector<CheckpointPosition> checkpoints = ParseCheckpoints(&file);
    std::vector<StartPositionT> standings = ParseStartPositions(&file);
    std::vector<ObjectPtr> objects = ParseObjects(&file);

    std::cerr << "Map " << mapName << " created!\n";
    std::cerr << "Desc: " << description << "\n";

    return std::make_shared<Map>(mapName, description, RealVec(sf::Vector2f(sizeX, sizeY)), view, friction, minimap,
                                 std::move(checkpoints),
                                 std::move(objects), std::move(standings));
}

std::vector<CheckpointPosition> MapManager::ParseCheckpoints(
        std::ifstream *file) const {
    int checkpointNumber;
    std::vector<CheckpointPosition> checkpoints;
    *file >> checkpointNumber;
    for (int i = 0; i < checkpointNumber; ++i) {
        float x, y, r;
        CheckpointPosition checkpoint;
        *file >> x >> y >> r;
        checkpoint = {x, y, MathUtil::DegreeToRadian(r)};
        checkpoints.push_back(checkpoint);
        std::cerr << "Checkpoint: " << x << ", " << y << ", " << r << "\n";
    }
    return checkpoints;
}

std::vector<StartPositionT> MapManager::ParseStartPositions(
        std::ifstream *file) const {
    int positionsNumber;
    std::vector<StartPositionT> startPositions;
    *file >> positionsNumber;
    for (int i = 0; i < positionsNumber; ++i) {
        float x, y, r;
        *file >> x >> y >> r;
        startPositions.push_back((StartPositionT) {x, y, MathUtil::DegreeToRadian(r)});
    }
    return startPositions;
}

std::vector<ObjectPtr> MapManager::ParseObjects(std::ifstream *file) const {
    std::string line, objectName;
    std::vector<ObjectPtr> objects;
    std::stringstream data;

    file->ignore(1);
    while (getline(*file, line)) {
        if (line[0] == '#') {
            continue;
        }
        float x, y, r;
        ObjectPtr object;
        data = std::stringstream(line);
        data >> objectName >> x >> y >> r;
        object = objectManager_->CreateObjectByName(
                objectName, RealVec(x, y), MathUtil::DegreeToRadian(r));
        objects.push_back(object);
    }
    return objects;
}

