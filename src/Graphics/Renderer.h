#pragma once

#include <bits/stdc++.h>
#include <Scene.h>
#include <GraphicsCommon.h>
#include "UI/UI.h"

enum ViewTypeE {
    VIEW_TYPE_SINGLE,
    VIEW_TYPE_MULTI
};

class Renderer {
public:
    Renderer(RenderWindowPtr renderWindow);

    void RenderScene(ScenePtr scene, ViewTypeE viewType);

    void RenderUI(UIPtr ui);

    void Clear();

    void Display();

private:
    void RenderCameraInViewport(ScenePtr scene, CameraPtr camera, sf::FloatRect viewport);

    RenderWindowPtr renderWindow_;
};
