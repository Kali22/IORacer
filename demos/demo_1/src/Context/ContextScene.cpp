/**
 *  @file
 *  @ingroup xxx
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#include <ContextScene.h>

ContextScene::ContextScene() {

}

ContextScene::~ContextScene() {

}

int ContextScene::GetCamerasCount() {
    return cameras_count;
}

const ContextCameraView &ContextScene::GetCameraView(int i) {
    return cameras[i].GetCameraView();
}
