/**
 *  @file
 *  @ingroup context_camera
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#include <ContextCameraView.h>

ContextCameraView::ContextCameraView(sf::View view) {
    camera_view = view;
}

ContextCameraView::~ContextCameraView() {

}

const sf::View &ContextCameraView::GetView() const {
    return camera_view;
}