
#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H
#include <cstring> // Include for string functions like strlen
#include "model/AppStorage.h"

class DeviceConfig
{
public:

    bool connect(AppStorage appStorage);
    bool isDeviceIdEmpty() const;
    const char *getDeviceId() const;
    float getSprayModuleActivateValue() const;
    float getWaterModuleActivateValue() const;

private:
    AppStorage appStorage;
};

#endif