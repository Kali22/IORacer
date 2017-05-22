#include "Activity.h"

Activity::Activity(std::string name) : name_(name), state_(ACTIVITY_STATE_INIT), userInterface_(nullptr) {

}

void Activity::Prepare(ActivityManagerPtr activityManager){
    activityManager_ = activityManager;
    userInterface_ = std::make_shared<UI>(shared_from_this());
}

std::string Activity::GetName() const {
    return name_;
}

ActivityStateE Activity::GetState() const {
    return state_;
}

void Activity::SetReady() {
    state_ = ACTIVITY_STATE_RUN;
}

UIPtr Activity::GetUI() const {
    return userInterface_;
}

ActivityManagerPtr Activity::GetActivityManager() const {
    return activityManager_;
}
