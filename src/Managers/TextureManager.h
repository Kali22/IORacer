#pragma once

#include <Texture/Texture.h>
#include <Texture/Sprite.h>

class TextureManager {
public:
    TextureManager();
    TexturePtr GetTextureByName(std::string name);
    SpritePtr GetSpriteFromTexture(std::string name);
private:
    const std::string resourcePath_ = "../resource/textures/";
    std::map<std::string, TexturePtr> textures_;
};

using TextureManagerPtr = std::shared_ptr<TextureManager>;

