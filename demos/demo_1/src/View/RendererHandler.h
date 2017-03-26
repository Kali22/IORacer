/**
 *  @defgroup renderer_handler Renderer handler
 *  Renderer device interface
 */

/**
 *  @file
 *  @ingroup renderer_handler
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#ifndef _RendererHandler_H_
#define _RendererHandler_H_

#include <ContextCameraView.h>

/**
 * Renderer handler
 */
class RendererHandler {
private:
    /// @TODO Add somehow main SFML window context to draw on the screen
    sf::Window &window;
public:
    /**
     * Create renderer handler.
     * @TODO pass sfml window handler??
     */
    RendererHandler(sf::Window &window);

    /**
     * Destroy
     * @param view
     */
     ~RendererHandler();

    /**
     * Draw view on screen.
     * @param view
     */
    void Render(const ContextCameraView &view);
};


#endif //RendererHandler
