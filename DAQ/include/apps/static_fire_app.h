#ifndef STATIC_FIRE_APP_H
#define STATIC_FIRE_APP_H

#include "app.h"

class StaticFire : public App{
private:
    bool isHam00wniaConnected;

public:
    StaticFire(){}
    ~StaticFire(){}

    static void appTask(void* arg);
};

#endif