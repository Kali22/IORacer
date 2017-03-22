/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#ifndef _MainView_H_
#define _MainView_H_

#include <SFML/Window.hpp>
#include "Context/ContextView.h"
#include <cstring>

class MainView {
private:
    int window_size_x;
    int window_size_y;
    sf::Window *window;
    std::string window_name;

public:
    MainView();

    ~MainView();

    sf::Window *GetWindow();

    void Initialize();

    void Render(const std::vector<ContextView &>::const_iterator views_list);
};


#endif //_MainView_H_
