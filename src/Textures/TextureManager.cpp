#include "TextureManager.h"

TextureManager::TextureManager() {
    std::ifstream file(resourcePath_ + "textures_list.cnfg");
    std::string line;
    std::string name;
    std::string fileName;
    std::stringstream data;

    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        data = std::stringstream(line);
        data >> name >> fileName;
        textures_.insert(std::pair<std::string, TexturePtr >(name, std::make_shared<Texture>(name, resourcePath_ + fileName)));
    }

}

TexturePtr TextureManager::GetTextureByName(std::string name) {
    std::map<std::string,TexturePtr>::iterator it = textures_.find(name);
    if (it != textures_.end())
        return textures_[name];
    else
        return nullptr;
}
