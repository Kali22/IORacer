#pragma once

#include <string>
#include <map>
#include <ObjectManager.h>
#include <Object.h>
#include "Map.h"

/**
 * @TODO -> Change map loader and add starting  positions!!!
 * @TODO -> Add minimap provider!?
 */
class MapManager {
public:
    MapManager(TextureManagerPtr textureManager, ObjectManagerPtr objectManager);

    MapPtr  CreateMap(std::string mapName);
private:
    const std::string cnfgFile_ = "maps_list.cnfg";

    const std::string resourcePath_ = "../resource/maps/";

    std::map<std::string, std::string> maps_;

    TextureManagerPtr textureManager_;

    ObjectManagerPtr objectManager_;
};

using MapManagerPtr = std::shared_ptr<MapManager>;