#ifndef NETWORKCONTRLLER_H
#define NETWORKCONTRLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WebServer.h>
#include "model/AppStorage.h"


class NetworkController
{
public:
  bool connect();
  bool run();
   String sensorData;
  AppStorage getAppStorage();
    void clearEEPROM();
    void initializeAppStorage();

private:
  AppStorage appStorage;
  WebServer webServer;
  void handleReport();
  void startServer();
  void handleSettings();
  void handleNetworkConfig();
  void handleNotFound();
  void handleSettingsConfig();
  void clearStorage();
 void  printStorage();
 void handleReset();
  bool isWebServerRunning = false;
  bool isStorageEmpty();
  const char *ssid = "SmartAgro";
  const char *password = "0123456789";
  const int channel = 10;       // WiFi Channel number between 1 and 13
  const bool hide_SSID = false; // To disable SSID broadcast -> SSID will not appear in a basic WiFi scan
  const int max_connection = 1;
};

#endif
