#ifndef STATIC_FIRE_APP_H
#define STATIC_FIRE_APP_H

#define STATIC_FIRE_APP_NUM 2

class StaticFire {
private:
    bool isHam00wniaConnected;

public:
    StaticFire();
    ~StaticFire();

    static void StaticFireApp(void);
};