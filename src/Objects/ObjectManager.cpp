#include "ObjectManager.h"
#include <Box.h>
#include <TruckTire.h>
#include <CheckPoint.h>
#include <Tire.h>
#include <VehicleObject.h>

ObjectManager::ObjectManager(TextureManagerPtr textureManager, b2World* world) :
        textureManager_(textureManager), world_(world) {
    std::ifstream file(resourcePath_ + "objects_list.cnfg");
    std::string line;
    std::stringstream data;
    std::string name;
    std::string textureName;
    int type;
    float radius, x, y;


    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        data = std::stringstream(line);
        data >> name >> textureName;
        data >> type;
        if (type == (int) OBJECT_SHAPE_RECT) {
            data >> x >> y;
        } else {
            data >> radius;
        }

        ObjectDesc desc;
        desc.name = name;
        desc.textureName = textureName;
        desc.objectShape = (ObjectShapeE) type;

        switch ((ObjectShapeE) type) {
            case OBJECT_SHAPE_RECT:
                desc.size = RealVec(sf::Vector2f(x, y));
                break;

            case OBJECT_SHAPE_CIRC:
                desc.radius = radius;
                break;
        }
        visualObjects_.insert(std::pair<std::string, ObjectDesc>(name, desc));
        std::cerr << "Object description loaded: [" << name << ", " << textureName << ", " << type << "]\n";
    }
}

ObjectPtr ObjectManager::GetObjectInstanceByName(const std::string&
objectName) {
    std::map<std::string,ObjectDesc>::iterator it = visualObjects_.find(objectName);
    if (it == visualObjects_.end())
        return nullptr;

    TexturePtr texture = textureManager_->GetTextureByName(visualObjects_[objectName].textureName);
    if (texture == nullptr) {
        std::cerr << "Texture name " << visualObjects_[objectName].textureName << " not found!\n";
        exit(1);
    }
    VisualObjectPtr visualObject = std::make_shared<VisualObject>
            (visualObjects_[objectName], texture);

    return GetObjectInstanceByName(objectName, visualObject);
}

// TODO pass Description to function
ObjectPtr ObjectManager::GetObjectInstanceByName(const std::string& objectName,
                                                 VisualObjectPtr visualObject) {
    if (objectName == "box") {
        return std::make_shared<Box>(world_, visualObject);
    }
    if (objectName == "tyre") {
        return std::make_shared<TruckTire>(world_, visualObject);
    }
    if (objectName == "checkpoint") {
        return std::make_shared<CheckPoint>(world_, visualObject);
    }
    if (objectName == "wheel") {
        return std::make_shared<Tire>(world_, visualObject);
    }
    if (objectName == "vehicle") {
        std::vector<TirePtr> tires;
        for (int i = 0; i < 4; i++) {
            TirePtr tire =
                    std::dynamic_pointer_cast<Tire>
                            (GetObjectInstanceByName("wheel"));
            assert(tire != nullptr);
            tires.push_back(tire);
        }
        return std::make_shared<VehicleObject>(world_, visualObject,
                                               tires);
    }
    std::cerr << "Unknown object" << objectName;
    exit(1);
}