#include "FirebaseHandler.h"
#include "addons/TokenHelper.h"
#include "utils/Logger.h"
#include "config.h"

/**
 * @brief Default constructor for the FirebaseHandler class.
 *
 * This constructor initializes the member variables of the class with default values.
 */

FirebaseHandler::FirebaseHandler()
    : isAuthenticated(false), elapsedMillis(0)
{
}

void FirebaseHandler::createSensorObjet(BLEServerController *bleCtr, SensorReader *sensorReader, ModuleController *moduleController)
{

    AppStorage *storage = bleCtr->getAppStorage();
    float soilMoisture = sensorReader->readMoisture();
    float atmosphericTemperature = sensorReader->readAtmosphericTemperature();
    bool willSprayOn = atmosphericTemperature > storage->sprayModuleActivateValue;
    bool willWaterModuleOn = soilMoisture < storage->waterModuleActivateValue;
    sensor_json.clear();
    sensor_json.add("action", "DATA");
    sensor_json.add("deviceUniqueId", DEVICE_UID);
    sensor_json.add("fcmUniqueId", fuid);
    sensor_json.add("deviceWifiLocalIP", WiFi.localIP().toString());
    sensor_json.add("soilMoisture", soilMoisture);
    sensor_json.add("soilTemperature", sensorReader->readTemperature());
    sensor_json.add("soilEC", String(sensorReader->readEconduc()));
    sensor_json.add("soilPH", sensorReader->readPh());
    sensor_json.add("soilNitrogen", String(sensorReader->readNitrogen()));
    sensor_json.add("soilPhosphorous", String(sensorReader->readPhosphorous()));
    sensor_json.add("soilPotassium", String(sensorReader->readPotassium()));
    sensor_json.add("atmosphericTemperature", atmosphericTemperature);
    sensor_json.add("sprayModuleActivateValue", storage->sprayModuleActivateValue);
    sensor_json.add("waterModuleActivateValue", storage->waterModuleActivateValue);
    sensor_json.add("atmosphericHumidity", sensorReader->readAtmosphericHumidity());
    sensor_json.add("sprayModuleStatus", moduleController->isSprayModuleOn);
    sensor_json.add("waterModuleStatus", moduleController->isWaterModuleOn);
    sensor_json.add("willSprayOn", willSprayOn);
    sensor_json.add("willWaterModuleOn", willWaterModuleOn);
     sensor_json.add("isWIFIConnected", isConnected);
    sensor_json.toString(bleCtr->sensorData, true);
    Logger::log(bleCtr->sensorData);
    uploadData();
    if (willSprayOn)
    {
        moduleController->activateSprayModule();
    }
    else
    {
        moduleController->deactivateSprayModule();
    }

    if (willWaterModuleOn)
    {
        moduleController->activateWaterMotor();
    }
    else
    {
        moduleController->deactivateWaterMotor();
    }
}

void FirebaseHandler::connect()
{
    sensorPath = "/sensors/";
    sensorPath.concat(DEVICE_UID);
    config.api_key = TOKEN;
    config.database_url = HOST_URL;
    Firebase.reconnectWiFi(true);
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        isAuthenticated = true;
        Logger::log("Firebase authentication successful");
        fuid = auth.token.uid.c_str();
    }
    else
    {
        Logger::log("Firebase authentication failed");
    }
    // Assign the callback function for the long running token generation task, see addons/TokenHelper.h
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Logger::log("Firebase initialized!");
    isConnected = true;
}

/**
 * @brief Uploads JSON data to the specified node in the Firebase database.
 *
 * This method checks if the connection is ready, the user is authenticated, and the update interval has elapsed before sending the provided JSON data.
 *
 * @param node The path to the node in the Firebase database where the data should be uploaded.
 *
 * @return true if the data upload was successful, false otherwise.
 */
void FirebaseHandler::uploadData()
{
    if (isConnected)
    {
        Logger::log("Sending data to Firebase:");
        if (millis() - elapsedMillis > UPDATE_INTRAVEL && isAuthenticated && Firebase.ready())
        {
            elapsedMillis = millis();
            if (Firebase.setJSON(fbdo, sensorPath, sensor_json))
            {
                Logger::log("Firebase data upload successful");
            }
            else
            {
                Logger::log("Firebase data upload failed: ");
                Serial.print(fbdo.errorReason());
                Logger::log("Error---Completd");
            }
        }
        else
        {
            Logger::log("Firebase is not ready or user is not authenticated");
        }
    }
}
