#include <Arduino.h>
#include "config.h"
#include "Application.h"
#include "public/Logger.h"

// Initialize the Application object with appropriate pins and configurations.
Application app(WATER_MOTOR_PIN, SPRAY_PIN, RX_PIN, TX_PIN, DHTPIN, DHTTYPE);

/**
 * @brief Put the ESP32 into deep sleep mode.
 * 
 * This function sets up the ESP32 to wake up after a predefined time
 * interval defined by DEEP_SLEEP_TIME.
 */
void esp32DeepSleep() {
    Logger::log("Going to deep sleep...");
  // Configure the timer to wake up the ESP32 after the specified time
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    // Go to sleep now
    Logger::log("Going to sleep now");
    delay(1000);  // Give time for the serial messages to be sent
    esp_deep_sleep_start();
}

/**
 * @brief Setup function for the ESP32.
 * 
 * This function initializes the Serial communication, begins the application,
 * and then puts the ESP32 into deep sleep.
 */
void setup() {
    Serial.begin(9600);          // Initialize Serial communication at 9600 baud rate.
    Logger::log("Setup begin");  // Log the setup start.

    app.begin();                 // Initialize the application.
    Logger::log("Setup end");    // Log the setup end.

   // esp32DeepSleep();             // Put the ESP32 into deep sleep.
}

/**
 * @brief Main loop function for the ESP32.
 * 
 * This function continuously runs the main application logic with a delay.
 */
void loop() {
    app.run();                   // Run the main application logic.
}
