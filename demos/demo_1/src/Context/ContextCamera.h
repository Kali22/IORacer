/**
 * @defgroup context_camera Context camera
 * @ingroup context_scene
 * Controls views and scene rendering methods.
 */

/**
 *  @file
 *  @ingroup context_camera
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#ifndef _ContextCamera_H_
#define _ContextCamera_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ContextCameraView.h>

/**
 * Context camera
 */
class ContextCamera {
private:
    /// View
    sf::View camera;
    /// Camera view
    ContextCameraView camera_view;
public:
    /**
     *  Create default camera
     */
    ContextCamera();

    /**
     * Destroy.
     */
    ~ContextCamera();

    /**
     * Return const copy of camera view.
     * @return
     */
    const ContextCameraView &GetCameraView();

    /**
     *  @TODO Object tracking?, moving?, zooming?, active,
     */
};


#endif //ContextCamera
