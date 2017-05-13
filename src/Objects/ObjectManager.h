#pragma once

#include <TextureManager.h>
#include <VisualObject.h>
#include <Object.h>
#include <CheckPoint.h>

class ObjectManager {
public:
    ObjectManager(TextureManagerPtr textureManager, b2World* world);
    ObjectPtr GetObjectInstanceByName(const std::string& objectName);
private:
    ObjectPtr GetObjectInstanceByName(const std::string& objectName,
                                      VisualObjectPtr visualObject);

    const std::string resourcePath_ = "../resource/objects/";
    b2World* world_;
    std::map<std::string, ObjectDesc> visualObjects_;

    TextureManagerPtr textureManager_;
};

using ObjectManagerPtr = std::shared_ptr<ObjectManager>;