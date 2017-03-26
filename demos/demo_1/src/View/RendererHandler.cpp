/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#include <RendererHandler.h>

RendererHandler::~RendererHandler() {

}

void RendererHandler::Render(const ContextCameraView &view) {
    /// @TODO Rendering view on the screen
}

RendererHandler::RendererHandler(sf::Window &window) : window(window) {

}
