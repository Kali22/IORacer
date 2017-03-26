/**
 * @defgroup context_scene
 * @ingroup context
 * Context drawable elements manager.
 */

/**
 *  @file
 *  @ingroup context_scene
 *  @author Jacek Łysiak <jaceklysiako.o@gmail.com>
 *  @date 3/26/17
 */

#ifndef _ContextScene_H_
#define _ContextScene_H_

#include <vector>
#include <ContextCamera.h>
#include "ContextCameraView.h"

class ContextScene {
private:
    /// Number of cameras
    int cameras_count;
    /// Cameras container
    std::vector<ContextCamera> cameras;

public:
    /**
     * Create scene.
     */
    ContextScene();
    /**
     * Destroy scene.
     */
    ~ContextScene();

    /**
     * Get # of cameras.
     * @return # of cameras
     */
    int GetCamerasCount();

    /**
     * Create context camera view and return.
     * @param i camera id
     * @return i-th camera view
     */
    const ContextCameraView &GetCameraView(int i);
};


#endif //ContextScene
