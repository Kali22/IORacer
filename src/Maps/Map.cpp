#include "Map.h"

/**
 * Creates map and prepare the map's world.
 * Map texture and physical dimensions given in configuration file,
 * determines scale which can be propagated further.
 * Once map is created, all object have to be scaled.
 */
Map::Map(std::string name, std::string description, RealVec size, TexturePtr view, TexturePtr friction,
         std::vector<CheckPointPtr> &&checkpoints, std::vector<ObjectPtr>
         &&objects) :
        mapName_(name),
        mapDescription_(description),
        mapSize_(size),
        checkpoints_(std::move(checkpoints)),
        objects_(std::move(objects)),
        startPosition_(sf::Vector2f(0, 0)) {
    // Get images and textures
    imageFriction_ = friction->GetTexture()->copyToImage();
    mapView_.setTexture(*view->GetTexture());
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
    // TODO move to separate class
    camera_.setCenter(300, 300);
    camera_.setSize(1200, 800);
    camera_.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

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

void Map::SetStartPosition(sf::Vector2f pos) {
    startPosition_ = pos;
}

sf::Vector2f Map::GetStartPosition() const {
    return startPosition_;
}

const sf::View &Map::GetCameraView() const {
    return camera_;
}

void Map::SetCameraViewPosition(const sf::Vector2f &pos) {
    sf::Vector2f margin = camera_.getSize();
    margin = margin / 2.0f;
    sf::Vector2u map_size = imageFriction_.getSize();
    sf::Vector2f new_pos = pos;
    new_pos.x = (pos.x < margin.x ? margin.x : pos.x);
    new_pos.x = (pos.x > map_size.x - margin.x ? map_size.x - margin.x : new_pos.x);
    new_pos.y = (pos.y < margin.y ? margin.y : pos.y);
    new_pos.y = (pos.y > map_size.y - margin.y ? map_size.y - margin.y : new_pos.y);
    camera_.setCenter(new_pos);
}

void Map::SetCameraViewZoom(float f) {
    camera_.zoom(f);
}

void Map::AlignCameraViewSize(const sf::Window &window) {
    sf::Vector2u wnd_size = window.getSize();
    camera_.setSize(wnd_size.x, wnd_size.y);
}
