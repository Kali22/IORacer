#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics/Texture.hpp>

class Texture {
public:
    Texture(std::string name, std::string path);

    sf::Texture *GetTexture();

private:
    std::string name_;
    sf::Texture texture_;
};

using TexturePtr = std::shared_ptr<Texture>;
