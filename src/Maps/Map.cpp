#include "Map.h"
#include <CheckPoint/CheckPoint.h>

/**
 * Creates map and prepare the map's world.
 * Map texture and physical dimensions given in configuration file,
 * determines scale which can be propagated further.
 * Once map is created, all object have to be scaled.
 */
Map::Map(std::string name, std::string description, RealVec size, TexturePtr view, TexturePtr friction,
         TexturePtr minimap, std::vector<CheckPointPtr> &&checkpoints, std::vector<ObjectPtr> &&objects,
         std::vector<StartPositionT> &&standings) :
        mapName_(name),
        mapDescription_(description),
        mapSize_(size),
        checkpoints_(std::move(checkpoints)),
        objects_(std::move(objects)),
        startPositions_(std::move(standings)) {
    // Get images and textures
    imageFriction_ = friction->GetTexture()->copyToImage();
    mapView_.setTexture(*view->GetTexture());
    minimapView_.setTexture(*minimap->GetTexture());

    auto textureMapSize = mapView_.getGlobalBounds();
    // Set origin in the middle
    mapView_.setOrigin(.5f * textureMapSize.width, .5f * textureMapSize.height);

    // Calculate once global scale, dominant dimension is height
    scalePixMeters_ = textureMapSize.height / size.y;
    // If map texture doesn't match physical proportions... rescale
    float widthScale = scalePixMeters_ * size.x / textureMapSize.width;
    if (widthScale < 0.99 || 1.01 < widthScale) {
        std::cerr << mapName_ << ": Map proportions are not correct!\n";
    }
    mapView_.setScale(widthScale, 1);

    for (auto obj : checkpoints_) {
        obj->Rescale(scalePixMeters_);
    }

    for (auto obj : objects_) {
        obj->Rescale(scalePixMeters_);
    }

    std::cerr << mapName_ << ": Map is ready!\n";
    std::cerr << mapName_ << ": width = " << mapSize_.x << " heigth = " << mapSize_.y << "!\n";
    std::cerr << mapName_ << ": width [px] = " << textureMapSize.width << " heigth [px] = " << textureMapSize.height << "!\n";
}

float Map::GetPixMetersScale() const {
    return scalePixMeters_;
}

float Map::GetFrictionModifier(const RealVec& pos) {
    unsigned int x = (unsigned int) (pos.x < 0 ? 0 : pos.x);
    unsigned int y = (unsigned int) (pos.y < 0 ? 0 : pos.y);
    sf::Color color = imageFriction_.getPixel(x, y);
    return 1.f - (color.b + color.r + color.g) / 256.0f / 3.0f;
}

void Map::Draw(RenderWindowPtr window) const {
    window->draw(mapView_);
    for (auto obj : checkpoints_) {
        obj->Draw(window);
    }

    for (auto obj : objects_) {
        obj->Draw(window);
    }
}

std::vector<CheckPointPtr> Map::GetCheckpoints() const {
    return checkpoints_;
}

StartPositionT Map::GetStartPosition(int position) const {
    return startPositions_[position];
}
