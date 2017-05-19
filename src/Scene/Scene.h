#pragma once


#include <bits/stdc++.h>
#include <Map.h>
#include <Texture/Texture.h>
#include <Drawable.h>
#include <Camera.h>

class Scene {
public:
    Scene(MapPtr map);

    void AddObject(ObjectPtr object);

    void AddCamera(int trackedObject, float refHeight, float screenFraction);

    void AddCamera(RealVec center, float refHeight, float screenFraction);

    CameraPtr GetCamera(int n);

    float GetScale() const;

    void Render(RenderWindowPtr renderWindow) const;
private:
    float scalePixInMeters_;

    MapPtr map_;
    std::vector<ObjectPtr> objects_; //!< Extra objects... Players or a etc.. :)
    std::vector<CameraPtr> cameras_; //!< Possible views...
};

using ScenePtr = std::shared_ptr<Scene>;

