#include <fstream>
#include <sstream>
#include <iostream>
#include "MapManager.h"
#include <CheckPoint/CheckPoint.h>
#include <TextureManager.h>
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

        maps_.insert(std::pair<std::string, std::string>(mapName, fileName));
        std::cerr << "Map description loaded: [" << mapName << ", " << fileName
                  << "]\n";
    }
}

MapPtr MapManager::CreateMap(std::string mapName) {
    std::cerr << "Creating map: " << mapName << "\n";
    std::map<std::string, std::string>::iterator it = maps_.find(mapName);
    if (it == maps_.end())
        return nullptr;

    std::ifstream file(resourcePath_ + maps_[mapName]);
    std::string line;
    std::string objectName;
    std::stringstream data;

    std::string description;
    float sizeX, sizeY;
    std::string textureViewName;
    std::string textureFrictionName;
    std::string textureMinimapName;
    TexturePtr view;
    TexturePtr friction;
    TexturePtr minimap;
    int checkpointNumber;
    int standingsNumber;
    std::vector <CheckPointPtr> checkpoints;
    std::vector <ObjectPtr> objects;
    std::vector <StartPositionT> standings;

    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        else
            break;
    }
    description = line;
    file >> sizeX >> sizeY;
    file >> textureViewName;
    file >> textureFrictionName;
    file >> textureMinimapName;
    file >> checkpointNumber;

    view = textureManager_->GetTextureByName(textureViewName);
    friction = textureManager_->GetTextureByName(textureFrictionName);
    minimap = textureManager_->GetTextureByName(textureMinimapName);

    for (int i = 0; i < checkpointNumber; ++i) {
        float x, y, r;
        CheckPointPtr checkpoint;
        file >> x >> y >> r;
        checkpoint = objectManager_->CreateCheckpoint(RealVec(x,  y), MathUtil::DegreeToRadian(r));
        if (checkpoint == nullptr) {
            std::cerr << "Checkpoint creating fail!";
            exit(1);
        }
        checkpoints.push_back(checkpoint);
    }
    file >> standingsNumber;
    for (int i = 0; i < standingsNumber; ++i) {
        float x, y, r;
        file >> x >> y >> r;
        standings.push_back((StartPositionT) {x, y,MathUtil::DegreeToRadian(r)});
    }
    file.ignore(1);
    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        float x, y, r;
        ObjectPtr object;
        data = std::stringstream(line);
        data >> objectName >> x >> y >> r;
        object = objectManager_->CreateObjectByName(objectName, RealVec(x,  y), MathUtil::DegreeToRadian(r));
        objects.push_back(object);
    }
    std::cerr << "Map " << mapName << " created!\n";
    std::cerr << "Desc: " << description << "\n";

    return std::make_shared<Map>(mapName, description, RealVec(sf::Vector2f(sizeX, sizeY)), view, friction, minimap, std::move(checkpoints),
                                 std::move(objects), std::move(standings));
}

