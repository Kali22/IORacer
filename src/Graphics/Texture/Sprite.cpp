#include "Sprite.h"

Sprite::Sprite(TexturePtr texture) {
    sprite_.setTexture(*texture->GetTexture());
    auto size = sprite_.getGlobalBounds();
    // Origin in graphics center
    sprite_.setOrigin(size.width * .5f, size.height * .5f);
}

void Sprite::Draw(RenderWindowPtr window) const {
    window->draw(sprite_);
}
