#pragma once

#include <bits/stdc++.h>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class Texture {
public:
    Texture(const std::string &name, const std::string &path);

    sf::Texture *GetTexture();

private:
    std::string name_;
    sf::Texture texture_;
};

using TexturePtr = std::shared_ptr<Texture>;
