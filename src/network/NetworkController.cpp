#include "NetworkController.h"
#include <WiFi.h>
#include <EEPROM.h>


bool NetworkController::connect()
{
  EEPROM.get(0, networkSCridentials);
  if (isStorageEmpty())
  {
    IPAddress local_ip(192, 168, 0, 1);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    Serial.println("WiFi SSID is not configured");
    Serial.println("\n[*] Creating AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password, channel, hide_SSID, max_connection);
    Serial.print("[+] AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());
    return false;
  }
  else
  {
    WiFi.begin(networkSCridentials.ssid, networkSCridentials.password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
     return true;
  }
}

bool NetworkController::isStorageEmpty()
{
  return (strlen(networkSCridentials.ssid) == 0) && (strlen(networkSCridentials.password) == 0);
}