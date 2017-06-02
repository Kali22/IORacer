#pragma once


#include <memory>

class ObjectManager;
using ObjectManagerPtr = std::shared_ptr<ObjectManager>;

class ActivityManager;
using ActivityManagerPtr = std::shared_ptr<ActivityManager>;
using WeakActivityManagerPtr = std::weak_ptr<ActivityManager>;

class CheckPointManager;
using CheckPointManagerPtr = std::shared_ptr<CheckPointManager>;
