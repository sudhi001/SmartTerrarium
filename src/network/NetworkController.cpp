#include "NetworkController.h"
#include <WiFi.h>

NetworkController::NetworkController(String ssid, String password):ssid(ssid),password(password)
{
}
void NetworkController::begin()
{
  WiFi.begin(ssid, password);
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
}
