#pragma once


#include <Map.h>
#include <bits/stdc++.h>
#include <string>
#include <ObjectManager.h>
#include <Object.h>

class MapManager {
public:
    MapManager(TextureManagerPtr textureManager, ObjectManagerPtr objectManager);

    MapPtr CreateMap(std::string mapName);

private:
    std::vector<CheckpointPosition> ParseCheckpoints(std::ifstream *file) const;

    std::vector<StartPositionT> ParseStartPositions(std::ifstream *file) const;

    std::vector<ObjectPtr> ParseObjects(std::ifstream *file) const;

    const std::string cnfgFile_ = "maps_list.cnfg";

    const std::string resourcePath_ = "../resource/maps/";

    std::map<std::string, std::string> maps_;

    TextureManagerPtr textureManager_;

    ObjectManagerPtr objectManager_;

    std::vector<ObjectPtr> AddBounds(float sizeX, float sizeY) const;
};

using MapManagerPtr = std::shared_ptr<MapManager>;
