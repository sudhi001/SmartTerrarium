#include "DeviceConfig.h"


bool DeviceConfig::connect(AppStorage appStorage)
{
    this-> appStorage= appStorage;
    return true;
}



float DeviceConfig::getSprayModuleActivateValue() const
{
    return appStorage.sprayModuleActivateValue;
}

float DeviceConfig::getWaterModuleActivateValue() const
{
    return appStorage.waterModuleActivateValue;
}

