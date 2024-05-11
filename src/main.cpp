#include <Arduino.h>
#include "config.h"
#include "Application.h"

Application app( WATER_MOTOR_PIN, SPRAY_PIN, RX_PIN, TX_PIN, DHTPIN, DHTTYPE);
void gotToDeepSleep()
{
  Serial.println("Going to sleep...");
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME);
  esp_deep_sleep_start();

}
void setup()
{
  Serial.begin(9600);
  app.begin();
  gotToDeepSleep();
}
void loop()
{
  app.run();
  delay(3000);
}