#include <fstream>
#include <sstream>
#include <iostream>
#include "MapManager.h"

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
    TexturePtr view;
    TexturePtr friction;
    int checkpointNumber;
    std::vector <CheckPointPtr> checkpoints;
    std::vector <ObjectPtr> objects;

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
    file >> checkpointNumber;
    for (int i = 0; i < checkpointNumber; ++i) {
        float x, y, r;
        CheckPointPtr checkpoint;
        file >> x >> y >> r;
        checkpoint = std::dynamic_pointer_cast<CheckPoint>
                (objectManager_->GetObjectInstanceByName("checkpoint"));
        if (checkpoint == nullptr) {
            std::cerr << "Checkpoint creating fail!";
            exit(1);
        }
        checkpoint->SetPosition(x, y);
        checkpoint->SetRotation(r);
        checkpoints.push_back(checkpoint);
    }
    file.ignore(1);
    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        float x, y, r;
        ObjectPtr object;
        data = std::stringstream(line);
        data >> objectName >> x >> y >> r;
        object = objectManager_->GetObjectInstanceByName(objectName);
        object->SetPosition(x, y);
        object->SetRotation(r);
        objects.push_back(object);
    }
    view = textureManager_->GetTextureByName(textureViewName);
    friction = textureManager_->GetTextureByName(textureFrictionName);

    std::cerr << "Map " << mapName << " created!\n";

    return std::make_shared<Map>(mapName, description,
                                 RealVec(sf::Vector2f(sizeX, sizeY)), view,
                                 friction, std::move(checkpoints),
                                 std::move(objects));
}

