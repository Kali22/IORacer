#pragma once


#include <bits/stdc++.h>
#include <Window.h>
#include <ActivityCommon.h>
#include <Renderer.h>
#include <Managers.h>
#include <TextureManager.h>
#include <CarComponentManager.h>
#include <PlayerManager.h>

class ActivityManager : public std::enable_shared_from_this<ActivityManager> {
public:
    ActivityManager(WindowPtr window, TextureManagerPtr textureManager,
                    CarComponentManagerPtr carComponentManager,
                    PlayerManagerPtr playerManager);

    void Poll();

    void AddActivity(ActivityPtr activity);

    void SetAsActive(std::string name);

    void RemoveActivity(std::string name);

    void Manage();

    bool IsRunning() const;

    void End();

    RendererPtr GetRenderer() const;

    TextureManagerPtr GetTextureManager() const;

    CarComponentManagerPtr GetCarComponentManager() const;

    PlayerManagerPtr GetPlayerManager() const;

private:
    WindowPtr window_;
    TextureManagerPtr textureManager_;
    CarComponentManagerPtr carComponentManager_;
    PlayerManagerPtr playerManager_;

    std::map<std::string, ActivityPtr> activities_;
    ActivityPtr active_;
};
