#include "NetworkController.h"
#include <WiFi.h>


bool NetworkController::connect(AppStorage* appStorage)
{
  bool isSSID = strlen(appStorage->ssid) == 0;
  bool isPassword = strlen(appStorage->password) == 0;
  if (isSSID && isPassword)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Disconnecting from current Wi-Fi network...");
      WiFi.disconnect(true); // Disconnect and clean up
      delay(1000);           // Wait for disconnection
    }

    WiFi.begin(appStorage->ssid, appStorage->password);
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
   return false;
}

