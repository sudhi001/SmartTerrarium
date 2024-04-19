#include "DeviceConfig.h"
#include <EEPROM.h>

bool DeviceConfig::connect()
{
    EEPROM.get(2, deviceConfigData);
    if (isDeviceIdEmpty())
    {
        deviceConfigData.sprayModuleActivateValue = 27;
        deviceConfigData.waterModuleActivateValue = 15;
        EEPROM.put(2, deviceConfigData);
        EEPROM.commit();
    }
    return isDeviceIdEmpty();
}
void DeviceConfig::updateDeviceId(char* deviceId) 
{

    strncpy(deviceConfigData.deviceId, deviceId, sizeof(deviceConfigData.deviceId) - 1);
    deviceConfigData.deviceId[sizeof(deviceConfigData.deviceId) - 1] = '\0'; // Ensure null-termination
    EEPROM.put(2, deviceConfigData);
    EEPROM.commit();
}

bool DeviceConfig::isDeviceIdEmpty() const
{
    return (strlen(deviceConfigData.deviceId) == 0);
}

const char *DeviceConfig::getDeviceId() const
{
    return deviceConfigData.deviceId;
}

float DeviceConfig::getSprayModuleActivateValue() const
{
    return deviceConfigData.sprayModuleActivateValue;
}

float DeviceConfig::getWaterModuleActivateValue() const
{
    return deviceConfigData.waterModuleActivateValue;
}

void DeviceConfig::setDeviceId(const char *deviceId)
{
    strncpy(deviceConfigData.deviceId, deviceId, sizeof(deviceConfigData.deviceId) - 1);
    deviceConfigData.deviceId[sizeof(deviceConfigData.deviceId) - 1] = '\0'; // Ensure null-termination
}

void DeviceConfig::setSprayModuleActivateValue(float value)
{
    deviceConfigData.sprayModuleActivateValue = value;
}

void DeviceConfig::setWaterModuleActivateValue(float value)
{
    deviceConfigData.waterModuleActivateValue = value;
}
