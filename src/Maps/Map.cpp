#include <Map.h>

/**
 * Creates map and prepare the map's world.
 * Map texture and physical dimensions given in configuration file,
 * determines scale which can be propagated further.
 * Once map is created, all object have to be scaled.
 */
Map::Map(std::string name, std::string description, RealVec size, TexturePtr view, TexturePtr friction,
         TexturePtr minimap, std::vector<InitialPosition> checkpoints, std::vector<ObjectPtr> objects,
         std::vector<InitialPosition> standings) :
        mapName_(name),
        mapDescription_(description),
        mapSize_(size),
        minimapTexture_(minimap),
        checkpoints_(checkpoints),
        objects_(objects),
        startPositions_(standings) {
    /// @TODO: Check imageFriction scaling
    /// @TODO: Check correctness of imageFriction data in GetFrictionModifier call

    GetImageAndTexture(view, friction);
    SetOrigin();
    SetScale(size);

    PrintCreationLog();
}

void Map::GetImageAndTexture(TexturePtr view, TexturePtr friction) {
    imageFriction_ = friction->GetTexture()->copyToImage();
    mapView_.setTexture(*view->GetTexture());
}

void Map::SetOrigin() {
    sf::FloatRect textureMapSize = mapView_.getGlobalBounds();
    // Set origin in the middle
    mapView_.setOrigin(.5f * textureMapSize.width, .5f * textureMapSize.height);
}

void Map::SetScale(RealVec size) {
    // Calculate once global scale, dominant dimension is height
    sf::FloatRect textureMapSize = mapView_.getGlobalBounds();
    scalePixMeters_ = textureMapSize.height / size.y;
    // If map texture doesn't match physical proportions... rescale
    float widthScale = scalePixMeters_ * size.x / textureMapSize.width;
    if (widthScale < 0.99 || 1.01 < widthScale) {
        std::cerr << mapName_ << ": Map proportions are not correct!\n";
    }
    mapView_.setScale(widthScale, 1);

    for (auto obj : objects_) {
        obj->Rescale(scalePixMeters_);
    }
}

void Map::PrintCreationLog() {
    sf::FloatRect textureMapSize = mapView_.getGlobalBounds();
    std::cerr << mapName_ << ": Map is ready!\n";
    std::cerr << mapName_ << ": width = " << mapSize_.x << " heigth = " << mapSize_.y << "!\n";
    std::cerr << mapName_ << ": width [px] = " << textureMapSize.width << " heigth [px] = " << textureMapSize.height
              << "!\n";
}
float Map::GetPixMetersScale() const {
    return scalePixMeters_;
}

float Map::GetFrictionModifier(const RealVec &pos) {
    /// @TODO Check Out of range position
    /// @TODO Validate
    unsigned int sx = imageFriction_.getSize().x;
    unsigned int sy = imageFriction_.getSize().y;
    unsigned int x = (unsigned int) (pos.GetScaledVector().x + sx * 0.5f);
    unsigned int y = (unsigned int) (pos.GetScaledVector().y + sy * 0.5f);
    x = std::min(x, sx);
    y = std::min(y, sy);

    sf::Color color = imageFriction_.getPixel(x, y);
    float res = 1.f - (color.b + color.r + color.g) / 256.0f / 3.0f;
    fprintf(stderr, "GetFrictionModifier( %f, %f, %f)[x: %d, y: %d] = (r: %d, g: %d, b: %d) ->  %f\n", pos.x, pos.y,
            pos.GetScale(), x, y, color.r, color.g, color.b, res);
    return res;
}

void Map::Draw(RenderWindowPtr window) const {
    window->draw(mapView_);
    for (auto obj : objects_) {
        obj->Draw(window);
    }
}

const std::vector<InitialPosition> &Map::GetCheckpoints() const {
    return checkpoints_;
}

InitialPosition Map::GetInitialPosition(int position) const {
    return startPositions_[position];
}

std::string Map::GetMapName() const {
    return mapName_;
}

TexturePtr Map::GetMinimapTexture() const {
    return minimapTexture_;
}

RealVec Map::GetSize() const {
    return mapSize_;
}
