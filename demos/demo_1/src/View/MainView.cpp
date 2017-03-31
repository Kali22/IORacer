/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 20.03.17
 */

#include <MainView.h>
#include <config/config_default.h>

MainView::MainView() : window(sf::VideoMode(WINDOW_SIZE_X_DEFAULT, WINDOW_SIZE_Y_DEFAULT), WINDOW_NAME_DEFAULT), renderer(window) {
    window_size_x = WINDOW_SIZE_X_DEFAULT;
    window_size_y = WINDOW_SIZE_Y_DEFAULT;
    window_name = WINDOW_NAME_DEFAULT;
}

MainView::~MainView() {

}

sf::Window *MainView::GetWindowHandler() {
    return &window;
}

void MainView::Initialize() {

}

RendererHandler &MainView::GetRendererHandler() {
    return renderer;
}
