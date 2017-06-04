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
    std::vector<InitialPosition> ParseCheckpoints(std::ifstream &file) const;

    std::vector<InitialPosition> ParseInitialPositions(std::ifstream &file) const;

    std::vector<ObjectPtr> ParseObjects(std::ifstream &file) const;

    const std::string cnfgFile_ = "maps_list.cnfg";

    const std::string resourcePath_ = "../resource/maps/";

    std::map<std::string, std::string> maps_;

    TextureManagerPtr textureManager_;

    ObjectManagerPtr objectManager_;

    std::vector<ObjectPtr> AddBounds(float sizeX, float sizeY) const;

    MapPtr ParseMapDescription(std::string mapName);
};

using MapManagerPtr = std::shared_ptr<MapManager>;
