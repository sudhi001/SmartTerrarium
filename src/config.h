#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions for RS485 communication
#define RX_PIN 16  // Define the receive pin for RS485
#define TX_PIN 17  // Define the transmit pin for RS485

// DHT Sensor setup
#define DHTPIN 4    // Define the pin for DHT sensor data
#define DHTTYPE DHT11  // Define the DHT sensor type (DHT11, DHT22, etc.)

// Pin definitions for Spray Module and Water Motor
#define SPRAY_PIN 27         // Define the pin for controlling the spray module
#define WATER_MOTOR_PIN 26   // Define the pin for controlling the water motor

// Device unique identifier and WiFi credentials
#define DEVICE_UID "1X"         // Define the unique identifier for the device
#define WIFI_SSID ""     // Define the WiFi network SSID
#define WIFI_PASSWORD ""  // Define the WiFi network password

// Constants for activation thresholds
#define SPRAY_MODULE_ACTIVATION_TEMPERATURE 27   // Temperature threshold to activate spray module
#define WATER_MODULE_ACTIVATION_MOISTURE 15      // Moisture threshold to activate water motor

// Firebase project details
#define API_KEY "-"  // Firebase API key
#define DATABASE_URL ""  // Firebase database URL

#endif
