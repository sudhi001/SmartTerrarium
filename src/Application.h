#include <Arduino.h>
#include <FirebaseESP32.h>
#include "network/firebase/FirebaseHandler.h"
#include "module/ModuleController.h"
#include "module/SensorReader.h"
#include "module/DeviceConfig.h"
#include "network/NetworkController.h"
#include <WiFi.h>

class Application
{

private:
    FirebaseHandler firebaseHandler;
    NetworkController networkController;
    ModuleController moduleController;
    SensorReader sensorReader;
    DeviceConfig deviceConfig;
    bool isConnected = false;
    bool isFirebaseConnected;
    bool isDeviceCofigured;
    bool isAllOkay = false;

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
        networkController.initializeAppStorage();
        isConnected = networkController.connect();
        if (isConnected)
        {
            AppStorage storage = networkController.getAppStorage();
            sensorReader.begin();
            moduleController.begin();
            isFirebaseConnected = firebaseHandler.connect(storage, HOST_URL, TOKEN);
            if (isFirebaseConnected)
            {
                isDeviceCofigured = deviceConfig.connect(storage);
                if (isDeviceCofigured)
                {
                    isAllOkay = true;
                }
            }
        }
    }

    void run()
    {
        networkController.run();
        if (isConnected)
        {
            float soilMoisture = sensorReader.readMoisture();
            float atmosphericTemperature = sensorReader.readAtmosphericTemperature();
            bool willSprayOn = atmosphericTemperature > deviceConfig.getSprayModuleActivateValue();
            bool willWaterModuleOn = soilMoisture < deviceConfig.getWaterModuleActivateValue();
            FirebaseJson sensor_json;
            sensor_json.add("deviceUniqueId", DEVICE_UID);
            sensor_json.add("fcmUniqueId", firebaseHandler.fuid);
            sensor_json.add("deviceWifiLocalIP", WiFi.localIP().toString());
            sensor_json.add("soilMoisture", soilMoisture);
            sensor_json.add("soilTemperature", sensorReader.readTemperature());
            sensor_json.add("soilEC", String(sensorReader.readEconduc()));
            sensor_json.add("soilPH", sensorReader.readPh());
            sensor_json.add("soilNitrogen", String(sensorReader.readNitrogen()));
            sensor_json.add("soilPhosphorous", String(sensorReader.readPhosphorous()));
            sensor_json.add("soilPotassium", String(sensorReader.readPotassium()));
            sensor_json.add("atmosphericTemperature", atmosphericTemperature);
            sensor_json.add("atmosphericHumidity", sensorReader.readAtmosphericHumidity());
            sensor_json.add("sprayModuleStatus", moduleController.isSprayModuleOn);
            sensor_json.add("waterModuleStatus", moduleController.isWaterModuleOn);
            sensor_json.add("willSprayOn", willSprayOn);
            sensor_json.add("willWaterModuleOn", willWaterModuleOn);
            sensor_json.toString(networkController.sensorData, true);
            Serial.println(networkController.sensorData);
            if (isAllOkay)
            {
                const char *sensors = "/sensors/";
                char *path = (char *)malloc(strlen(sensors) + strlen(DEVICE_UID) + 1);
                if (path != NULL)
                {
                    strcpy(path, sensors);
                    strcat(path, DEVICE_UID);
                    firebaseHandler.uploadData(path, sensor_json);
                    free(path);
                }
            }

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