#include <Arduino.h>
#include "config.h"
#include "Application.h"

Application app(API_KEY, DATABASE_URL, WIFI_SSID, WIFI_PASSWORD,
                WATER_MOTOR_PIN, SPRAY_PIN, RX_PIN, TX_PIN, DHTPIN, DHTTYPE, DEVICE_UID,
                SPRAY_MODULE_ACTIVATION_TEMPERATURE, WATER_MODULE_ACTIVATION_MOISTURE);
void setup()
{
  Serial.begin(9600);
  app.begin();
  delay(3000);
}
void loop()
{
  app.run();
}