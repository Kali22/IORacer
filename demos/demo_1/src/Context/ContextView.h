/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _ContextView_H_
#define _ContextView_H_

#include <vector>
#include <SFML/Graphics.hpp>

/**
 *  Drawable context representation
 */
class ContextView {
private:
    /// List of all drawable elements
    std::vector<sf::Drawable> drawable_elements;
    /// List of cameras to draw on the screen
    std::vector<sf::View> cameras;
    /// View needed to redraw
    bool updated;
public:
    ContextView();

    ~ContextView();

    const std::vector<sf::Drawable>::const_iterator GetDrawable();

    const std::vector<sf::View>::const_iterator GetCameras();

    bool IsHidden();

    bool IsActive();

    bool IsUpdated();
};


#endif //_ContextView_H_
