#ifndef BLE_SERVER_CONTROLLER_H
#define BLE_SERVER_CONTROLLER_H

#include <Arduino.h>
#include "model/AppStorage.h"
#include <BLEDevice.h>

class BLEServerController
{
public:
    bool deviceConnected = false;
    String sensorData;
    AppStorage *getAppStorage();
    void connect();
    void processCMD(String received_json);
    void sendAction(String action,String msg);
    void run();
    void sendLog(String log);

private:
    BLECharacteristic *sSendString;
    AppStorage appStorage;
    void clearStorage();
    void clearEEPROM();
    void printStorage();
};

#endif
