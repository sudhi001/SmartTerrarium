#include "public/FirebaseHandler.h"
#include "addons/TokenHelper.h"
#include "public/Logger.h"
#include "config.h"

/**
 * @brief Default constructor for the FirebaseHandler class.
 *
 * This constructor initializes the member variables of the class with default values.
 */

FirebaseHandler::FirebaseHandler()
    : elapsedMillis(0), isConnected(false)
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
    auth.user.email = FB_USER_EMAIL;
    auth.user.password = FB_USER_PASSWORD;
    config.max_token_generation_retry = 5;
    Firebase.reconnectWiFi(true);
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Logger::log("Getting User UID");
    while ((auth.token.uid) == "")
    {
        Serial.print('.');
        delay(1000);
    }
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
        if (Firebase.isTokenExpired())
        {
            Firebase.refreshToken(&config);
            Serial.println("Refresh token");
        }
        Logger::log("Sending data to Firebase:");
        if ((millis() - elapsedMillis > UPDATE_INTRAVEL) || (elapsedMillis == 0))
        {
            if (Firebase.ready())
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
        else
        {
            unsigned long timeRemaining = UPDATE_INTRAVEL - (millis() - elapsedMillis);
            Logger::log("Network delay is below desired time");
            // Convert remaining time to seconds
            unsigned long timeRemainingSeconds = timeRemaining / 1000;
            char remainingTimeMsg[50];
            sprintf(remainingTimeMsg, "Time remaining until next send (s): %lu", timeRemainingSeconds);
            Logger::log(remainingTimeMsg);
        }
    }
}
