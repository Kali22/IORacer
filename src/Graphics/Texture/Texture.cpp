#include "Texture.h"

Texture::Texture(const std::string &name, const std::string &path) : name_(name) {
    texture_.loadFromFile(path);
    std::cerr << "Loaded texture \"" << name << "\" from: " + path + "\n";
}


sf::Texture *Texture::GetTexture() {
    return &texture_;
}
