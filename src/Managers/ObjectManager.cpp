#include "ObjectManager.h"
#include <GameObjects/CheckPoint/CheckPoint.h>
#include <GameObjects/Vehicle/Vehicle.h>
#include <TextureManager.h>
#include <ObjectDesc.h>

ObjectManager::ObjectManager(TextureManagerPtr textureManager, b2World* world) :
        textureManager_(textureManager), world_(world) {
    std::ifstream file(resourcePath_ + "objects_list.cnfg");
    std::string line;
    std::stringstream data;
    std::string name;
    std::string textureName;
    std::string dynamicType;
    int type;
    float radius, x, y, mass;


    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        data = std::stringstream(line);
        data >> name >> textureName >> dynamicType >> mass;
        data >> type;
        if (type == (int) OBJECT_SHAPE_RECT) {
            data >> x >> y;
        } else {
            data >> radius;
        }

        ObjectDesc desc;
        desc.name = name;
        for (auto it : ObjectsMap) {
            if (it.second == name) {
                desc.objectType = it.first;
                break;
            }
        }
        desc.textureName = textureName;
        desc.objectShape = (ObjectShapeE) type;
        desc.mass = mass;
        desc.dynamic = dynamicType == "dynamic";

        switch ((ObjectShapeE) type) {
            case OBJECT_SHAPE_RECT:
                desc.size = RealVec(sf::Vector2f(x, y));
                break;

            case OBJECT_SHAPE_CIRC:
                desc.radius = radius;
                break;
        }
        objectDesc_.insert(std::pair<std::string, ObjectDesc>(name, desc));
        std::cerr << "Object description loaded: [" << name << ", " << textureName << ", " << type << "]\n";
    }
}

VehiclePtr ObjectManager::CreateVehicle(int id, const RealVec &pos, float rot, const VehicleSetupT &setup, MapPtr map) {
    std::vector<WheelPtr> wheels;
    for(int i = 0; i < 4; ++i)
        wheels.push_back(CreateWheel(pos, rot));
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_VEHICLE], pos, rot);
    VisualObjectPtr chassis = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_VEHICLE]);
    return std::make_shared<Vehicle>(id, body, chassis, std::move(wheels), setup, map);
}

WheelPtr ObjectManager::CreateWheel(const RealVec &pos, float rot) {
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_WHEEL], pos, rot);
    VisualObjectPtr wheel = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_WHEEL]);
    return std::make_shared<Wheel>(body, wheel);
}

CheckPointPtr ObjectManager::CreateCheckpoint(int id, const RealVec &pos, float rot) {
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_CHECK_POINT], pos, rot);
    VisualObjectPtr checkpoint = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_CHECK_POINT]);
    checkpoint->Rescale(pos.GetScale());
    return std::make_shared<CheckPoint>(id, body, checkpoint);
}

ObjectPtr ObjectManager::CreateTire(const RealVec &pos, float rot) {
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_TIRE], pos, rot);
    VisualObjectPtr tire = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_TIRE]);
    return std::make_shared<Object>(body, tire, OBJECT_TYPE_TIRE);
}

ObjectPtr ObjectManager::CreateBox(const RealVec &pos, float rot) {
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_BOX], pos, rot);
    VisualObjectPtr box = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_BOX]);
    return std::make_shared<Object>(body, box, OBJECT_TYPE_BOX);
}

VisualObjectPtr ObjectManager::GetVisualObjectInstanceByName(const std::string &objectName) {
    std::map<std::string,ObjectDesc>::iterator it = objectDesc_.find(objectName);
    if (it == objectDesc_.end()) {
        std::cerr << "Object name " << objectName << " not found!\n";
        exit(1);
    }

    TexturePtr texture = textureManager_->GetTextureByName(objectDesc_[objectName].textureName);
    if (texture == nullptr) {
        std::cerr << "Texture name " << objectDesc_[objectName].textureName << " not found!\n";
        exit(1);
    }
    return std::make_shared<VisualObject>(objectDesc_[objectName], texture);
}

b2Body *ObjectManager::InitializeBody(const std::string &objectName, const RealVec &pos, float rot) {
    std::map<std::string,ObjectDesc>::iterator it = objectDesc_.find(objectName);
    if (it == objectDesc_.end()) {
        std::cerr << "Object name " << objectName << " not found!\n";
        exit(1);
    }
    ObjectDesc objectDesc = it->second;

    b2BodyDef body_Def;
    body_Def.linearDamping = 2;
    body_Def.angularDamping = 2;
    body_Def.position.x = pos.x;
    body_Def.position.y = pos.y;
    body_Def.angle = rot;
    if (objectDesc.dynamic)
        body_Def.type = b2_dynamicBody;
    else
        body_Def.type = b2_staticBody;
    b2Body *body = world_->CreateBody(&body_Def);

    if (objectDesc.objectShape == OBJECT_SHAPE_CIRC) {
        b2CircleShape shape;
        float density = objectDesc.mass / objectDesc.radius / objectDesc.radius / b2_pi;
        shape.m_radius = objectDesc.radius;
        body->CreateFixture(&shape, density);
    } else if (objectDesc.objectShape == OBJECT_SHAPE_RECT){
        b2FixtureDef fixtureDef;
        b2PolygonShape shape;
        float density = objectDesc.mass / objectDesc.size.x / objectDesc.size.y;
        shape.SetAsBox(objectDesc.size.x * 0.5f, objectDesc.size.y * 0.5f);
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        if (objectDesc.objectType == OBJECT_TYPE_CHECK_POINT) { // Special case...
            fixtureDef.isSensor = true;
            fixtureDef.density = 0;
        }
        body->CreateFixture(&fixtureDef);
    }
    return body;
}

ObjectPtr ObjectManager::CreateObjectByName(const std::string &name, const RealVec &pos, float rot) {
    std::map<ObjectTypeE, std::string>::iterator it = ObjectsMap.begin();
    while(it != ObjectsMap.end() && it->second != name)
        it++;
    if (it == ObjectsMap.end()) {
        std::cerr << "Object name " << name << " not found!\n";
        exit(1);
    }
    ObjectPtr obj;
    switch (it->first) {
        case OBJECT_TYPE_BOX:
            obj = CreateBox(pos, rot);
            break;
        case OBJECT_TYPE_TIRE:
            obj = CreateTire(pos, rot);
            break;
        default:
            std::cerr << "Cannot create " << name << " just by name!\n";
            exit(1);
    }
    return obj;
}
