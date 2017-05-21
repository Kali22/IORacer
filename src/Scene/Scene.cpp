#include "Scene.h"
#include <Vehicle.h>

/** Scene is composed of: map, cameras and objects - which are not included in map, i.e. cars.
 * At the beginning map pointer is passed as argument.
 * Map determines world's scale.
 * Each time when map and scene is created, objects are rescaled.
 * */
Scene::Scene(MapPtr map) : map_(map) {

}

void Scene::AddObject(VehiclePtr object) {
    object->Rescale(map_->GetPixMetersScale());
    objects_.push_back(object);
}

CameraPtr Scene::GetCamera(int n) {
    if (n >= cameras_.size()) {
        return nullptr;
    }

    return cameras_[n];
}

float Scene::GetScale() const {
    return map_->GetPixMetersScale();
}

void Scene::Render(RenderWindowPtr renderWindow) const {
    // First - map backgorund
    map_->Draw(renderWindow);
    // Second - scene objects
    for (auto object : objects_) {
      object->Draw(renderWindow);
    }
}

void Scene::AddCamera(int trackedObject, float refHeight, float screenFraction) {
    if (trackedObject >= objects_.size() || trackedObject < 0) {
        std::cerr << "Object doesn't exist!\n";
        exit(1);
    }
    CameraPtr camera = std::make_shared<Camera>(objects_[trackedObject], refHeight, screenFraction);
    cameras_.push_back(camera);
}

void Scene::AddCamera(RealVec center, float refHeight, float screenFraction) {
    CameraPtr camera = std::make_shared<Camera>(center, refHeight, screenFraction);
    cameras_.push_back(camera);
}
