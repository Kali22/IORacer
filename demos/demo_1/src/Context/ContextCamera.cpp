/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#include <ContextCamera.h>

ContextCamera::ContextCamera() : camera_view(camera) {
    /// sf::View constructor creates a default view of (0, 0, 1000, 1000)
}

ContextCamera::~ContextCamera() {

}

const ContextCameraView &ContextCamera::GetCameraView() {
    camera_view = ContextCameraView(camera); // Update
    return camera_view;
}
