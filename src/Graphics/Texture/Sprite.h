#pragma once


#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <Drawable.h>
#include <Texture.h>

class Sprite : public Drawable {
public:
    Sprite(TexturePtr texture);

    void Draw(RenderWindowPtr window) const;

private:
    sf::Sprite sprite_;
};

using SpritePtr = std::shared_ptr<Sprite>;
