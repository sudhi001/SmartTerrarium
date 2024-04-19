#include <Arduino.h>
#include <FirebaseESP32.h>
#include "network/firebase/FirebaseHandler.h"
#include "module/ModuleController.h"
#include "module/SensorReader.h"
#include "module/DeviceConfig.h"
#include "network/NetworkController.h"

class Application
{

private:
    FirebaseJson sensor_json;
    FirebaseHandler firebaseHandler;
    NetworkController networkController;
    ModuleController moduleController;
    SensorReader sensorReader;
    DeviceConfig deviceConfig;
    bool isConnected;
    bool isFirebaseConnected;
    bool isDeviceCofigured;

public:
    // Constructor to initialize members with appropriate parameters
    Application(
        int waterMotorPin, int sprayPin,
        int rxPin, int txPin, int dhtPin, uint8_t dhtType)
        : moduleController(waterMotorPin, sprayPin),
          sensorReader(rxPin, txPin, dhtPin, dhtType)
    {
    }

    void begin()
    {
        isConnected = networkController.connect();
        if (isConnected)
        {
            isFirebaseConnected = firebaseHandler.connect();
            if (isFirebaseConnected)
            {
                isDeviceCofigured = deviceConfig.connect();
                if (isDeviceCofigured)
                {
                    sensorReader.begin();
                    moduleController.begin();
                }
            }
        }
    }

    void run()
    {
        if (isConnected)
        {
            float soilMoisture = sensorReader.readMoisture();
            float atmosphericTemperature = sensorReader.readAtmosphericTemperature();
            bool willSprayOn = atmosphericTemperature > deviceConfig.getSprayModuleActivateValue();
            bool willWaterModuleOn = soilMoisture < deviceConfig.getWaterModuleActivateValue();
            FirebaseJson sensor_json;
            sensor_json.add("deviceUniqueId", deviceConfig.getDeviceId());
            sensor_json.add("fcmUniqueId", firebaseHandler.fuid);
            sensor_json.add("deviceWifiLocalIP", String(WiFi.localIP()));
            sensor_json.add("soilMoisture", String(soilMoisture));
            sensor_json.add("soilTemperature", String(sensorReader.readTemperature()));
            sensor_json.add("soilEC", String(sensorReader.readEconduc()));
            sensor_json.add("soilPH", String(sensorReader.readPh()));
            sensor_json.add("soilNitrogen", String(sensorReader.readNitrogen()));
            sensor_json.add("soilPhosphorous", String(sensorReader.readPhosphorous()));
            sensor_json.add("soilPotassium", String(sensorReader.readPotassium()));
            sensor_json.add("atmosphericTemperature", String(atmosphericTemperature));
            sensor_json.add("atmosphericHumidity", String(sensorReader.readAtmosphericHumidity()));
            sensor_json.add("sprayModuleStatus", String(moduleController.isSprayModuleOn));
            sensor_json.add("waterModuleStatus", String(moduleController.isWaterModuleOn));
            sensor_json.add("willSprayOn", String(willSprayOn));
            sensor_json.add("willWaterModuleOn", String(willWaterModuleOn));

            String jsonStr;
            sensor_json.toString(jsonStr, true);
            Serial.println(jsonStr);

            firebaseHandler.uploadData("/sensors", jsonStr);

            if (willSprayOn)
            {
                moduleController.activateSprayModule();
            }
            else
            {
                moduleController.deactivateSprayModule();
            }

            if (willWaterModuleOn)
            {
                moduleController.activateWaterMotor();
            }
            else
            {
                moduleController.deactivateWaterMotor();
            }
        }
    }
};