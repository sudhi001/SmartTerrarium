#include "public/BLEServerController.h"
#include "public/FirebaseHandler.h"
#include "config.h"
#include <string.h>
#include <EEPROM.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "public/Logger.h"

class ConnectionServerCallbacks : public BLEServerCallbacks
{
private:
    BLEServerController *bleServerControllerPtr;

public:
    ConnectionServerCallbacks(BLEServerController *serverController) : bleServerControllerPtr(serverController) {}

    void onConnect(BLEServer *pServer)
    {
        bleServerControllerPtr->deviceConnected = true;
        Logger::log("Connected");
        bleServerControllerPtr->sendLog("Device Connected");
        pServer->startAdvertising();
        bleServerControllerPtr->sendAction("BONJOUR","");
        Logger::log("Blutooth advertise started");
    };

    void onDisconnect(BLEServer *pServer)
    {
        bleServerControllerPtr->deviceConnected = false;
        Logger::log("Disconnected");
        pServer->startAdvertising();
        Logger::log("Blutooth advertise started");
    }
};

class WriteString : public BLECharacteristicCallbacks
{
private:
    BLEServerController *bleServerControllerPtr;

public:
    WriteString(BLEServerController *serverController) : bleServerControllerPtr(serverController) {}

    void onWrite(BLECharacteristic *pCharacteristic)
    {
        Logger::log("Received String:START");
        const char *charData = pCharacteristic->getValue().c_str();
        Logger::log(String(charData));
        bleServerControllerPtr->processCMD(charData);
        Logger::log("Received String:END");
        bleServerControllerPtr->sendLog("Device Received a request");
    }
};
AppStorage *BLEServerController::getAppStorage()
{
    return &appStorage;
}

void BLEServerController::connect()
{
    // clearStorage();
    EEPROM.begin(sizeof(AppStorage));
    EEPROM.get(0, appStorage);
    EEPROM.end();
    printStorage();
    BLEDevice::init(DEVICE_NAME);
    BLEServer *btServer = BLEDevice::createServer();
    btServer->setCallbacks(new ConnectionServerCallbacks(this));
    BLEService *sRecive = btServer->createService(RECIVE);
    uint32_t cwrite = BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE;

    BLECharacteristic *sReciveString = sRecive->createCharacteristic(RECIVE_STRING, cwrite);
    sReciveString->setCallbacks(new WriteString(this));

    BLEService *sSend = btServer->createService(SEND);
    uint32_t cnotify = BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE |
                       BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE;

    sSendString = sSend->createCharacteristic(SEND_STRING, cnotify);
    sSendString->addDescriptor(new BLE2902());
    String json = "{\"action\":\"BONJOUR\"}";
    sSendString->setValue(json.c_str());

    sRecive->start();
    sSend->start();

    BLEAdvertising *pAdvertising = btServer->getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    pAdvertising->start();
    Logger::log("");
    Logger::log("Blutooth advertise started");
}
void BLEServerController::run()
{
    if (deviceConnected)
    {
        Logger::log("Send Data to BLE:START");
        sSendString->setValue(sensorData.c_str());
        sSendString->notify();
        Logger::log("Send Data to BLE:END");
    }
}
void BLEServerController::sendAction(String action,String msg)
{
    if (deviceConnected)
    {
        String json = "{\"action\":\"";
        json.concat(action);
        json.concat("\",\"msg\":\"");
        json.concat(msg);
        json.concat("\"}");
        sSendString->setValue(json.c_str());
        sSendString->notify();
    }
}
void BLEServerController::sendLog(String log)
{
       Logger::log(log);
    if (deviceConnected)
    {
        String json = "{\"action\":\"LOG\",\"log\":\"";
        json.concat(log);
        json.concat("\"}");
        sSendString->setValue(json.c_str());
        sSendString->notify();
    }
}

void BLEServerController::processCMD(String jsonString)
{

 if (!jsonString.isEmpty()) {
    DynamicJsonDocument jsonDocument(4024);
    DeserializationError error = deserializeJson(jsonDocument, jsonString);
    if (error)
    {
         Logger::log(jsonString);
        sendLog("deserializeJson() failed: ");
        sendLog(error.f_str());
        return;
    }

    String action = jsonDocument["action"];
     Logger::log("Event Occured");
     Logger::log(action);
    if (action == "RESET")
    {
        clearStorage();
        ESP.restart();
    }
    else if (action == "CONFIGURE")
    {
        String ssidValue = jsonDocument["ssid"];
        String passwordValue = jsonDocument["password"];
        strncpy(appStorage.ssid, ssidValue.c_str(), sizeof(appStorage.ssid) - 1);
        appStorage.ssid[sizeof(appStorage.ssid) - 1] = '\0';

        strncpy(appStorage.password, passwordValue.c_str(), sizeof(appStorage.password) - 1);
        appStorage.password[sizeof(appStorage.password) - 1] = '\0';

        // Set default values
        appStorage.sprayModuleActivateValue = 27;
        appStorage.waterModuleActivateValue = 15;

        // Write to EEPROM
        EEPROM.begin(sizeof(AppStorage)); // Initialize EEPROM with struct size
        EEPROM.put(0, appStorage);        // Store the struct at address 0
        EEPROM.commit();                  // Commit the data to EEPROM
        EEPROM.end();                     // Release EEPROM resources
        sendLog("ESP need to be restart.");
        printStorage();
        ESP.restart();
    }else if (action == "SET_PROPERTY")
    {
        float sprayModuleActivateValue = jsonDocument["sprayModuleActivateValue"];
        float waterModuleActivateValue = jsonDocument["waterModuleActivateValue"];
        appStorage.sprayModuleActivateValue = sprayModuleActivateValue;
        appStorage.waterModuleActivateValue = waterModuleActivateValue;

        // Write to EEPROM
        EEPROM.begin(sizeof(AppStorage)); // Initialize EEPROM with struct size
        EEPROM.put(0, appStorage);        // Store the struct at address 0
        EEPROM.commit();                  // Commit the data to EEPROM
        EEPROM.end();                     // Release EEPROM resources
        sendLog("ESP need to be restart.");
        printStorage();
        sendAction("CHANGED_PROPERTY","");
        ESP.restart();
    }
 }else{
        Logger::log("String is empty");
 }
}

void BLEServerController::clearStorage()
{

    String empty = "";
    empty.toCharArray(appStorage.ssid, sizeof(appStorage.ssid));
    empty.toCharArray(appStorage.password, sizeof(appStorage.password));

    // Ensure null termination
    appStorage.ssid[sizeof(appStorage.ssid) - 1] = '\0';
    appStorage.password[sizeof(appStorage.password) - 1] = '\0';
    // Set default values for float fields
    appStorage.sprayModuleActivateValue = 0.0;
    appStorage.waterModuleActivateValue = 0.0;
    clearEEPROM();

    EEPROM.begin(sizeof(AppStorage));
    EEPROM.get(0, appStorage);
    EEPROM.end();
    printStorage();
}
void BLEServerController::clearEEPROM()
{
    size_t storageSize = sizeof(AppStorage);
    EEPROM.begin(storageSize);
    for (int i = 0; i < storageSize; i++)
    {
        EEPROM.write(i, 0);
    }
    // Commit the changes to EEPROM
    EEPROM.commit();
    // End EEPROM usage
    EEPROM.end();
    sendLog("EEPROM cleared successfully.");
    printStorage();
}
void BLEServerController::printStorage()
{
    Logger::log("Network Credentials:");
    Logger::log("SSID: ");
    Logger::log(String(appStorage.ssid));
    Logger::log("Password: ");
    Logger::log(String(appStorage.password));
     Logger::log("Water Activation: ");
    Logger::log(String(appStorage.waterModuleActivateValue));
     Logger::log("Spray Activation: ");
    Logger::log(String(appStorage.sprayModuleActivateValue));
     String ssid=String(appStorage.ssid);
    String message = "your ssid is ";
    message.concat(ssid);
    sendLog(message);
}