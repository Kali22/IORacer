#include "ObjectManager.h"

#include <CheckPoint.h>
#include <Vehicle.h>
#include <MathUtil.h>

ObjectManager::ObjectManager(TextureManagerPtr textureManager, b2World *world) :
        textureManager_(textureManager), world_(world) {
    std::ifstream file(resourcePath_ + "objects_list.cnfg");
    std::string line;

    while (getline(file, line)) {
        std::stringstream data;
        float radius, x, y;
        int type;

        if (line[0] == '#') {
            continue;
        }
        ObjectDesc desc;
        data = std::stringstream(line);
        data >> desc.name >> desc.textureName >> line >> desc.mass;
        desc.dynamic = line == "dynamic";
        data >> type;
        desc.objectShape = (ObjectShapeE) type;
        if (type == (int) OBJECT_SHAPE_RECT) {
            data >> x >> y;
            desc.size = RealVec(sf::Vector2f(x, y));
        } else {
            data >> radius;
            desc.radius = radius;
        }

        for (auto it : ObjectsMap) {
            if (it.second == desc.name) {
                desc.objectType = it.first;
                break;
            }
        }

        objectDesc_.emplace(desc.name, desc);
        std::cerr << "Object description loaded: [" << desc.name << ", "
                  << desc.textureName << ", " << type << "]\n";
    }
}

VehiclePtr ObjectManager::CreateVehicle(int id, const RealVec &pos, float
rot, const VehicleSetupT &setup, MapPtr map, CarConfigurationPtr carConfiguration) {
    std::vector<WheelPtr> wheels;
    for (int i = 0; i < 4; ++i)
        wheels.push_back(CreateWheel(pos, rot));
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_VEHICLE], pos, rot);
    VisualObjectPtr chassis = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_VEHICLE]);
    return std::make_shared<Vehicle>(id, body, chassis, std::move(wheels),
                                     setup, carConfiguration, map);
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

ObjectPtr ObjectManager::CreateCone(const RealVec &pos, float rot) {
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_CONE], pos, rot);
    VisualObjectPtr cone = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_CONE]);
    return std::make_shared<Object>(body, cone, OBJECT_TYPE_CONE);
}

ObjectPtr ObjectManager::CreateStone(const RealVec &pos, float rot) {
    b2Body *body = InitializeBody(ObjectsMap[OBJECT_TYPE_STONE], pos, rot);
    VisualObjectPtr stone = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_STONE]);
    return std::make_shared<Object>(body, stone, OBJECT_TYPE_STONE);
}

VisualObjectPtr ObjectManager::GetVisualObjectInstanceByName(const std::string &objectName) {
    std::map<std::string, ObjectDesc>::iterator it = objectDesc_.find(objectName);
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
    std::map<std::string, ObjectDesc>::iterator it = objectDesc_.find(objectName);
    if (it == objectDesc_.end()) {
        std::cerr << "Object name " << objectName << " not found!\n";
        exit(1);
    }
    ObjectDesc objectDesc = it->second;

    b2BodyDef bodyDef;
    bodyDef.linearDamping = 2;
    bodyDef.angularDamping = 2;
    bodyDef.position.x = pos.x;
    bodyDef.position.y = pos.y;
    bodyDef.angle = rot;
    if (objectDesc.dynamic) {
        bodyDef.type = b2_dynamicBody;
    } else {
        bodyDef.type = b2_staticBody;
    }
    b2Body *body = world_->CreateBody(&bodyDef);

    CreateFixture(body, objectDesc);
    return body;
}

ObjectPtr ObjectManager::CreateObjectByName(const std::string &name, const RealVec &pos, float rot) {
    std::map<ObjectTypeE, std::string>::iterator it = ObjectsMap.begin();
    while (it != ObjectsMap.end() && it->second != name)
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
        case OBJECT_TYPE_CONE:
            obj = CreateCone(pos, rot);
            break;
        case OBJECT_TYPE_STONE:
            obj = CreateStone(pos, rot);
            break;
        default:
            std::cerr << "Cannot create " << name << " just by name!\n";
            exit(1);
    }
    return obj;
}

void ObjectManager::CreateFixture(b2Body *body, ObjectDesc objectDesc) const {
    if (objectDesc.objectShape == OBJECT_SHAPE_CIRC) {
        b2CircleShape shape;
        float density = objectDesc.mass / objectDesc.radius / objectDesc.radius / b2_pi;
        shape.m_radius = objectDesc.radius;
        body->CreateFixture(&shape, density);
    } else if (objectDesc.objectShape == OBJECT_SHAPE_RECT) {
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
}

ObjectPtr ObjectManager::CreateBound(const RealVec &pos, float length, bool horizontal) {
    std::string objectName = "bound";
    std::map<std::string, ObjectDesc>::iterator it = objectDesc_.find(objectName);
    if (it == objectDesc_.end()) {
        std::cerr << "Object name " << objectName << " not found!\n";
        exit(1);
    }
    ObjectDesc objectDesc = it->second;
    objectDesc.size.x = length;

    b2BodyDef bodyDef;
    bodyDef.position.x = pos.x;
    bodyDef.position.y = pos.y;
    bodyDef.angle = MathUtil::DegreeToRadian(90 * (!horizontal));
    bodyDef.type = b2_staticBody;
    b2Body *body = world_->CreateBody(&bodyDef);

    CreateFixture(body, objectDesc);
    VisualObjectPtr obj = GetVisualObjectInstanceByName(ObjectsMap[OBJECT_TYPE_BOUND]);
    return std::make_shared<Object>(body, obj, OBJECT_TYPE_BOUND);
}
