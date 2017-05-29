#pragma once

#include <bits/stdc++.h>
#include <Drawable.h>
#include <Renderer.h>
#include <Managers.h>
#include <UI.h>
#include <Event.h>

enum ActivityStateE {
    ACTIVITY_STATE_INIT,
    ACTIVITY_STATE_RUN,
    ACTIVITY_STATE_END,
};

class Activity : public std::enable_shared_from_this<Activity> {
public:
    Activity(std::string name);

    virtual void Init() = 0;

    virtual void Run() = 0;

    virtual void End() = 0;

    virtual void EventAction(Event event) = 0;

    void Prepare(ActivityManagerPtr activityManager);

    UIPtr GetUI() const;

    std::string GetName() const;

    ActivityStateE GetState() const;

    void SetReady();

    ActivityManagerPtr GetActivityManager() const;

protected:
    void SetTitleStyle(UITextBoxPtr textBox);

    void SetButtonStyle(UITextBoxPtr button);

    void SetTextBoxStyle(UITextBoxPtr textBox);

    std::string name_;
    ActivityStateE state_;

    UIPtr userInterface_;
    ActivityManagerPtr activityManager_;
};
