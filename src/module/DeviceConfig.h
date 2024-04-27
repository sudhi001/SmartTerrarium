
#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H
#include <cstring> // Include for string functions like strlen
#include "model/AppStorage.h"

class DeviceConfig
{
public:

    bool connect(AppStorage appStorage);
    float getSprayModuleActivateValue() const;
    float getWaterModuleActivateValue() const;

private:
    AppStorage appStorage;
};

#endif