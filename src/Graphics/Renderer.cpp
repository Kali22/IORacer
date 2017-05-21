#include "Renderer.h"

Renderer::Renderer(RenderWindowPtr renderWindow) : renderWindow_(renderWindow) {
}

/**
 * Camera view render on screen.
 * It can be very easily extended to any type of multi camera rendering.
 */
void Renderer::RenderScene(ScenePtr scene, ViewTypeE viewType) {
    CameraPtr camera0;
    CameraPtr camera1;
    switch (viewType) {
        case VIEW_TYPE_SINGLE:
            camera0 = scene->GetCamera(0);
            /* Single player - render on full screen (0, 0, 1, 1). */
            RenderCameraInViewport(scene, camera0, sf::FloatRect(0, 0, 1, 1));
            break;
        case VIEW_TYPE_MULTI:
            camera0 = scene->GetCamera(0);
            camera1 = scene->GetCamera(1);
            /* Multi player */
            /* Render first player on left half-screen. */
            RenderCameraInViewport(scene, camera0, sf::FloatRect(0, 0, 0.5, 1));
            /* Render second player on right half-screen. */
            RenderCameraInViewport(scene, camera1, sf::FloatRect(0.5, 0, 0.5, 1));
            break;
    }
}

/**
 * Rendering camera view on monitor screen basing on viewport rectangle.
 * Remember! It contains fractional units relative to renderer screen. -> viewport = [left, top, width, height]
 */
void Renderer::RenderCameraInViewport(ScenePtr scene, CameraPtr camera, sf::FloatRect viewport) {
    if (camera == nullptr) {
        std::cerr << "Camera doesn't exist!\n";
        exit(1);
    }
    auto screenSize = renderWindow_->getSize();
       sf::View view;
    sf::Vector2f viewSize;
    view.setViewport(viewport);
    // Recalculate screen size to fit viewport - This causes cropping visible map area but proportions are saved.
    screenSize.x *= viewport.width;
    screenSize.y *= viewport.height;
    // Calculate view size.
    viewSize.y = camera->GetReferenceHeight() * scene->GetScale() / camera->GetScreenFraction();
    viewSize.x = viewSize.y * screenSize.x / screenSize.y;
    view.setSize(viewSize);
    view.setCenter(camera->GetCenter().GetScaledVector());
    /* Setup view and  let it render! */
    renderWindow_->setView(view);
    scene->Render(renderWindow_);
    renderWindow_->setView(renderWindow_->getDefaultView());
}

void Renderer::RenderUI(UIPtr ui) {
    auto screenSize = renderWindow_->getSize();
    int size = ui->GetElementsCount();
    sf::FloatRect relSize;
    sf::FloatRect absSize;
    std::map<std::string, UIElementPtr>::iterator it = ui->GetElements();
    for (int i = 0; i < size; ++i, it++) {
        UIElementPtr el = it->second;
        relSize = el->GetRelativeSize();
        absSize.width = screenSize.x * relSize.width;
        absSize.height = screenSize.y * relSize.height;
        absSize.left = screenSize.x * relSize.left;
        absSize.top = screenSize.y * relSize.top;
        el->SetAbsoluteSize(absSize);
        el->Render(renderWindow_);
    }
}

void Renderer::Clear() {
    renderWindow_->clear();
}

void Renderer::Display() {
    renderWindow_->display();
}
