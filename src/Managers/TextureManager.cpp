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
        std::cerr << "Texture: " << name << ", " << resourcePath_ + fileName << "\n";
        TexturePtr texture = std::make_shared<Texture>(name, resourcePath_ + fileName);
        textures_.emplace(name, texture);
    }

}

TexturePtr TextureManager::GetTextureByName(std::string name) {
    std::map<std::string, TexturePtr>::iterator it = textures_.find(name);
    if (it != textures_.end())
        return textures_[name];
    else
        return nullptr;
}

SpritePtr TextureManager::GetSpriteFromTexture(std::string name) {
    TexturePtr texture = GetTextureByName(name);
    if (texture == nullptr) {
        std::cerr << "No such texture in resources!" << std::endl;
        exit(1);
    }
    return std::make_shared<Sprite>(texture);
}
