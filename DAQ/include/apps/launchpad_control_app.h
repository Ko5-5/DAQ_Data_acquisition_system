#ifndef LAUNCHPAD_CONTROL_APP_H
#define LAUNCHPAD_CONTROL_APP_H

class LaunchpadControl {
private:
    bool isOBCConnected;

public:
    LaunchpadControl();
    ~LaunchpadControl();

    static void LaunchpadControlApp(void);
};