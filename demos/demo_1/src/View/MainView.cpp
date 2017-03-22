/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include "MainView.h"
#include "config/config_default.h"

MainView::MainView() {
    window_size_x = WINDOW_SIZE_X_DEFAULT;
    window_size_y = WINDOW_SIZE_Y_DEFAULT;
    window_name = WINDOW_NAME_DEFAULT;
}

MainView::~MainView() {
    delete window;
}

sf::Window *MainView::GetWindow() {
    return window;
}

void MainView::Initialize() {
    window = new sf::Window(sf::VideoMode(window_size_x, window_size_y), window_name.c_str());
}
