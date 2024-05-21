#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

#include "model/AppStorage.h"
#include "config.h"
#include "utils/Logger.h"

class NetworkController {
public:
    bool connect(AppStorage *appStorage);

private:
    bool checkSSID(AppStorage *appStorage);
    bool checkPassword(AppStorage *appStorage);
    void logSSIDAndPassword(bool isSSID, bool isPassword);
    void disconnectFromWiFi();
    void connectToWiFi(AppStorage *appStorage);
};

#endif

