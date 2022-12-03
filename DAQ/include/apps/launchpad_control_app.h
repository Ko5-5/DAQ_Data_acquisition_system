#ifndef LAUNCHPAD_CONTROL_APP_H
#define LAUNCHPAD_CONTROL_APP_H

#include "app.h"

class LaunchpadControl : public App {
  private:
    bool isOBCConnected;

  public:
    LaunchpadControl(){}
    ~LaunchpadControl(){}

    static void appTask(void* arg);
};

#endif