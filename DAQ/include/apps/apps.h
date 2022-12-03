#ifndef APPS_H
#define APPS_H

#include "apps/launchpad_control_app.h"
#include "apps/sensor_tester_app.h"
#include "apps/static_fire_app.h"

enum class AppName : uint8_t { NO_APP, SENSOR_APP, STATIC_FIRE_APP, LAUNCHPAD_APP };

#endif