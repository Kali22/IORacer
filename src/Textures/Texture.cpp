#include "Texture.h"

Texture::Texture(std::string name, std::string path) : name_(name) {
    texture_.loadFromFile(path);
    std::cerr << "Loaded texture \"" << name << "\" from: " + path + "\n";
}

sf::Texture *Texture::GetTexture() {
    return &texture_;
}

