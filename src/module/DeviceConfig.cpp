#include "DeviceConfig.h"


bool DeviceConfig::connect(AppStorage appStorage)
{
    this-> appStorage= appStorage;
    return isDeviceIdEmpty();
}

bool DeviceConfig::isDeviceIdEmpty() const
{
    return (strlen(appStorage.deviceId) == 0);
}

const char *DeviceConfig::getDeviceId() const
{
    return appStorage.deviceId;
}

float DeviceConfig::getSprayModuleActivateValue() const
{
    return appStorage.sprayModuleActivateValue;
}

float DeviceConfig::getWaterModuleActivateValue() const
{
    return appStorage.waterModuleActivateValue;
}

