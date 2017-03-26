/**
 *  @file
 *  @ingroup context_camera
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#ifndef _ContextCameraView_H_
#define _ContextCameraView_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
 * Context camera view class.
 * Read-only interface for @see ContextCamera
 * <a href="https://www.sfml-dev.org/tutorials/2.4/graphics-view.php">How SFML view works?</a>
 */
class ContextCameraView {
private:
    sf::View camera_view;
public:
    /**
     * Create and copy view.
     * @param view camera view
     */
    ContextCameraView(sf::View view);

    /**
     * Destroy.
     * @note unnecessary?
     */
    ~ContextCameraView();

    /**
     * Get view.
     * @return view
     */
    const sf::View &GetView() const;
};

#endif //ContextCameraView
