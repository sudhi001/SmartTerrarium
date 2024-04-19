#include <Arduino.h>
#include "config.h"
#include "Application.h"

Application app( WATER_MOTOR_PIN, SPRAY_PIN, RX_PIN, TX_PIN, DHTPIN, DHTTYPE);
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