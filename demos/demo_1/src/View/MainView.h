/**
 * @defgroup main_view Main View
 *
 */

/**
 *  @file
 *  @ingroup main_view
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _MainView_H_
#define _MainView_H_

#include <SFML/Window.hpp>
#include <RendererHandler.h>
#include <cstring>

class MainView {
private:
    int window_size_x;
    int window_size_y;
    sf::Window window;
    std::string window_name;
    RendererHandler renderer;

public:
    MainView();

    ~MainView();

    sf::Window *GetWindowHandler();

    void Initialize();

    RendererHandler &GetRendererHandler();
};


#endif //_MainView_H_
