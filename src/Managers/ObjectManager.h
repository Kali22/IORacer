#pragma once


#include <Managers.h>
#include <ObjectTypes.h>
#include <Map.h>
#include <VehicleSetup.h>
#include <Object.h>
#include <TextureManager.h>
#include <CarConfiguration.h>

class ObjectManager {
public:
    ObjectManager(TextureManagerPtr textureManager, b2World *world);

    /* Game object creation. */
    VehiclePtr CreateVehicle(int id, const RealVec &pos, float rot, const VehicleSetup &setup, MapPtr map,
                             CarConfigurationPtr carConfiguration);

    CheckPointPtr CreateCheckpoint(int id, const RealVec &pos, float rot);

/*
    ObjectPtr CreateTire(const RealVec &pos, float rot);

    ObjectPtr CreateBox(const RealVec &pos, float rot);

    ObjectPtr CreateCone(const RealVec &pos, float rot);

    ObjectPtr CreateStone(const RealVec &pos, float rot);
*/
    ObjectPtr CreateObjectByName(const std::string &name, const RealVec &pos, float rot);

    ObjectPtr CreateBound(const RealVec &pos, float length, bool horizontal);

private:
    void CreateFixture(b2Body *body, ObjectDesc objectDesc) const;

    b2Body *InitializeBody(const std::string &objectName, const RealVec &pos, float rot);

    VisualObjectPtr GetVisualObjectInstanceByName(const std::string &objectName);

    WheelPtr CreateWheel(const RealVec &pos, float rot);

    ObjectPtr CreateObject(ObjectTypeE type, const RealVec &pos, float rot);


    const std::string resourcePath_ = "../resource/objects/";
    std::map<std::string, ObjectDesc> objectDesc_;
    b2World *world_;
    TextureManagerPtr textureManager_;
};
