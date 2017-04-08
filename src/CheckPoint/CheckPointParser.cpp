#include <vector>
#include <string>
#include <fstream>

#include <RectangleArea.h>
#include <CheckPointParser.h>
#include <MathUtil.h>

CheckPointParser::CheckPointParser(b2World *world, float scale)
        : world_(world), scale_(scale) {
}

std::vector<CheckPointPtr> CheckPointParser::ParseFile(const std::string &file) {
    input_.open(file);
    std::vector<CheckPointPtr> res;
    std::string paramName;
    float val1, val2;

    // Parse rectangle Size
    input_ >> paramName >> val1;
    input_ >> paramName >> val2;

    b2Size_ = b2Vec2(val1, val2);
    sfmlSize_ = sf::Vector2f(val1 * scale_, val2 * scale_);

    while (input_ >> paramName >> val1) {
        struct RectangleParams params;
        ParseCheckPoint(&params);
        CheckPointPtr checkPoint = std::make_shared<CheckPoint>(new RectangleArea(world_, params));
        res.push_back(checkPoint);
    }

    input_.close();
    return res;
}

void CheckPointParser::ParseCheckPoint(struct RectangleParams *params) {
    std::string paramName;
    float val1, val2;

    input_ >> paramName >> val1;
    input_ >> paramName >> val2;
    params->b2Pos = b2Vec2(val1, val2);
    params->sfmlPos = sf::Vector2f(val1 * scale_, val2 * scale_);

    input_ >> paramName >> val1;
    params->sfmlAngle = val1;
    params->b2Angle = MathUtil::DegreeToRadian(val1);

    params->b2Size = b2Size_;
    params->sfmlSize = sfmlSize_;
}

