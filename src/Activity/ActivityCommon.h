#pragma once


#include <memory>

class Activity;

using ActivityPtr = std::shared_ptr<Activity>;
using WeakActivityPtr = std::weak_ptr<Activity>;
