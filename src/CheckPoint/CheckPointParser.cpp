#include <vector>
#include <string>
#include <fstream>

#include <RectangleArea.h>
#include <CheckPointParser.h>
#include <MathUtil.h>

CheckPointParser::CheckPointParser(b2World *world, float scale)
        : world_(world), scale_(scale) {
}

std::vector<CheckPointPtr>
CheckPointParser::ParseFile(const std::string &file) {
    input_.open(file);

    ParseRectangleSize();

    // Load texture.
    sf::IntRect textureSize(0, 0, (int) sfmlSize_.x, (int) sfmlSize_.y);
    checkPointTexture_.loadFromFile("../resource/checkpoint.png", textureSize);

    std::vector<CheckPointPtr> res = ParseCheckPoints();

    input_.close();
    return res;
}

void CheckPointParser::ParseRectangleSize() {
    std::string paramName; // Unused.
    float val1, val2;

    input_ >> paramName >> val1;
    input_ >> paramName >> val2;
    b2Size_ = b2Vec2(val1, val2);
    sfmlSize_ = sf::Vector2f(val1 * scale_, val2 * scale_);
}

std::vector<CheckPointPtr> CheckPointParser::ParseCheckPoints() {
    std::vector<CheckPointPtr> res;
    std::string paramName;
    int val;

    while (input_ >> paramName >> val) {
        struct RectangleParams params;
        ParseCheckPoint(&params);
        auto *rectangleArea = new RectangleArea(world_, params);
        auto checkPoint = std::make_shared<CheckPoint>(rectangleArea,
                                                       &checkPointTexture_);
        res.push_back(checkPoint);
    }
    return res;
}

void CheckPointParser::ParseCheckPoint(struct RectangleParams *params) {
    std::string paramName;
    float val1, val2;

    // Read position.
    input_ >> paramName >> val1;
    input_ >> paramName >> val2;
    params->b2Pos = b2Vec2(val1, val2);
    params->sfmlPos = sf::Vector2f(val1 * scale_, val2 * scale_);

    // Read Angle.
    input_ >> paramName >> val1;
    params->sfmlAngle = val1;
    params->b2Angle = MathUtil::DegreeToRadian(val1);

    // Save declared size;
    params->b2Size = b2Size_;
    params->sfmlSize = sfmlSize_;
}

