#pragma once

#include <vector>
#include <string>
#include <fstream>

#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <CheckPoint.h>

class CheckPointParser {
public:
    CheckPointParser(b2World* world, float scale);

    std::vector<CheckPoint*> ParseFile(const std::string& file);
private:
    void ParseCheckPoint(struct RectangleParams* params);

    b2Vec2 b2Size_;
    sf::Vector2f sfmlSize_;
    b2World* world_;
    float scale_;
    std::ifstream input_;
};

