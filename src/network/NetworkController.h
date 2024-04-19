#ifndef NETWORKCONTRLLER_H
#define NETWORKCONTRLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

struct NetworCridentials
{
  char ssid[32];
  char password[32];
};

class NetworkController
{
public:
  bool connect();

private:
  NetworCridentials networkSCridentials;
  bool isStorageEmpty();
  const char *ssid = "SmartAgro";
  const char *password = "Sm123";
  const int channel = 10;       // WiFi Channel number between 1 and 13
  const bool hide_SSID = false; // To disable SSID broadcast -> SSID will not appear in a basic WiFi scan
  const int max_connection = 1;
};

#endif
