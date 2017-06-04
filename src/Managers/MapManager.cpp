#include <MapManager.h>
#include <MathUtil.h>

MapManager::MapManager(TextureManagerPtr textureManager, ObjectManagerPtr objectManager) :
        textureManager_(textureManager), objectManager_(objectManager) {

    std::ifstream file(resourcePath_ + cnfgFile_);
    std::string line;
    std::stringstream data;
    std::string mapName;
    std::string fileName;

    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        data = std::stringstream(line);
        data >> mapName >> fileName;

        maps_.emplace(mapName, fileName);
        std::cerr << "Map description loaded: [" << mapName << ", " << fileName << "]\n";
    }
}

MapPtr MapManager::CreateMap(std::string mapName) {
    std::cerr << "Creating map: " << mapName << std::endl;
    std::map<std::string, std::string>::iterator it = maps_.find(mapName);
    if (it == maps_.end()) {
        std::cerr << "Map: " << mapName << " does not exist" << std::endl;
        return nullptr;
    }
    return ParseMapDescription(mapName);
}

std::string SkipComments(std::ifstream &file) {
    std::string description;
    while (getline(file, description)) {
        if (description[0] != '#') {
            break;
        }
    }
    return description;
}

MapPtr MapManager::ParseMapDescription(std::string mapName) {
    std::ifstream file(resourcePath_ + maps_[mapName]);
    std::string description = SkipComments(file);

    float sizeX, sizeY;
    std::string viewName, frictionName, minimapName;
    file >> sizeX >> sizeY >> viewName >> frictionName >> minimapName;
    TexturePtr view = textureManager_->GetTextureByName(viewName);
    TexturePtr friction = textureManager_->GetTextureByName(frictionName);
    TexturePtr minimap = textureManager_->GetTextureByName(minimapName);

    std::vector<InitialPosition> checkpoints = ParseCheckpoints(file);
    std::vector<InitialPosition> standings = ParseInitialPositions(file);
    std::vector<ObjectPtr> objects = ParseObjects(file);
    std::vector<ObjectPtr> bounds = AddBounds(sizeX, sizeY);
    objects.insert(objects.end(), bounds.begin(), bounds.end());

    std::cerr << "Map " << mapName << " created!\n";
    std::cerr << "Desc: " << description << "\n";

    return std::make_shared<Map>(mapName, description, RealVec(sf::Vector2f(sizeX, sizeY)), view, friction, minimap,
                                 std::move(checkpoints), std::move(objects), std::move(standings));
}

std::vector<InitialPosition> MapManager::ParseCheckpoints(std::ifstream &file) const {
    int checkpointNumber;
    std::vector<InitialPosition> checkpoints;
    file >> checkpointNumber;
    float x, y, r;
    for (int i = 0; i < checkpointNumber; ++i) {
        InitialPosition checkpoint;
        file >> x >> y >> r;
        checkpoint = {x, y, MathUtil::DegreeToRadian(r)};
        checkpoints.push_back(checkpoint);
        std::cerr << "Checkpoint: " << x << ", " << y << ", " << r << "\n";
    }
    return checkpoints;
}

std::vector<InitialPosition> MapManager::ParseInitialPositions(std::ifstream &file) const {
    int positionsNumber;
    std::vector<InitialPosition> startPositions;
    file >> positionsNumber;
    float x, y, r;
    for (int i = 0; i < positionsNumber; ++i) {
        file >> x >> y >> r;
        startPositions.push_back((InitialPosition) {x, y, MathUtil::DegreeToRadian(r)});
    }
    return startPositions;
}

std::vector<ObjectPtr> MapManager::ParseObjects(std::ifstream &file) const {
    std::string line, objectName;
    std::vector<ObjectPtr> objects;
    std::stringstream data;

    file.ignore(1);
    float x, y, r;
    ObjectPtr object;
    while (getline(file, line)) {
        if (line[0] == '#') {
            continue;
        }
        data = std::stringstream(line);
        data >> objectName >> x >> y >> r;
        object = objectManager_->CreateObjectByName(
                objectName, RealVec(x, y), MathUtil::DegreeToRadian(r));
        objects.push_back(object);
    }
    return objects;
}

std::vector<ObjectPtr> MapManager::AddBounds(float sizeX, float sizeY) const {
    std::vector<ObjectPtr> bounds;
    bounds.push_back(objectManager_->CreateBound(RealVec(sizeX / 2, 0), sizeY, false));  //right
    bounds.push_back(objectManager_->CreateBound(RealVec(-sizeX / 2, 0), sizeY, false)); //left
    bounds.push_back(objectManager_->CreateBound(RealVec(0, -sizeY / 2), sizeX, true));  //up
    bounds.push_back(objectManager_->CreateBound(RealVec(0, sizeY / 2), sizeX, true));   //down
    return bounds;
}
