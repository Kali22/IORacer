#pragma once


#include <bits/stdc++.h>
#include <Map.h>
#include <Texture.h>
#include <Drawable.h>
#include <Camera.h>

class Scene {
public:
    Scene(MapPtr map);

    void AddObject(VehiclePtr object);

    void AddCamera(unsigned trackedObject, float refHeight,
                   float screenFraction);

    void AddCamera(RealVec center, float refHeight, float screenFraction);

    CameraPtr GetCamera(unsigned n);

    float GetScale() const;

    void Render(RenderWindowPtr renderWindow) const;

private:
    MapPtr map_;
    std::vector<VehiclePtr> vehicles_; //!< Extra objects... Players or a etc.. :)
    std::vector<CameraPtr> cameras_; //!< Possible views...
};

using ScenePtr = std::shared_ptr<Scene>;
