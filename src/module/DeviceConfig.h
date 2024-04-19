
#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H
#include <cstring> // Include for string functions like strlen

struct DeviceConfigData
{
     char deviceId[32];
    float sprayModuleActivateValue;
    float waterModuleActivateValue;
};

class DeviceConfig
{
public:
    bool connect();
    void updateDeviceId(char *deviceId);
    bool isDeviceIdEmpty() const;
    const char *getDeviceId() const;
    float getSprayModuleActivateValue() const;
    float getWaterModuleActivateValue() const;

    // Methods to set configuration data
    void setDeviceId(const char *deviceId);
    void setSprayModuleActivateValue(float value);
    void setWaterModuleActivateValue(float value);

private:
    DeviceConfigData deviceConfigData;
};

#endif