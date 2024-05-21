#include <Arduino.h>
#include "config.h"
#include "Application.h"

Application app(WATER_MOTOR_PIN, SPRAY_PIN, RX_PIN, TX_PIN, DHTPIN, DHTTYPE);
SemaphoreHandle_t xMutex;

void gotToDeepSleep()
{
  Serial.println("Going to sleep...");
  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME);
  esp_deep_sleep_start();
}
void taskOne(void *parameters)
{
   while(1)
  {
    Serial.println("Network Task Executing");
    if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
    {
      app.taskOne();
      xSemaphoreGive(xMutex);
    }
    Serial.println("Network Task Completed");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void taskTwo(void *parameters)
{
    while(1) 
  {
    Serial.println("Network Task Executing");
    if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
    {
      app.taskTwo();
      xSemaphoreGive(xMutex);
    }
    Serial.println("Network Task Completed");
    vTaskDelay(UPDATE_INTRAVEL / portTICK_PERIOD_MS);
  }
}
void setup()
{
  Serial.begin(9600);
  Serial.println("App Begin");
  xMutex = xSemaphoreCreateMutex();
  app.begin();
  xTaskCreate(
      taskOne,
      "Main Task",
      2048,
      NULL,
      0,
      NULL);
  xTaskCreate(
      taskTwo,
      "Network Task",
      2048,
      NULL,
      1,
      NULL);
  Serial.println("App Setup end");
  // Delay to allow tasks to run briefly before deep sleep
 vTaskDelay(1000 / portTICK_PERIOD_MS);
  gotToDeepSleep();
}

void loop()
{
  Serial.println("Loop");
}