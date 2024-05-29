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


#define DEVICE_NAME "SMART_IOT"  
// Device unique identifier and WiFi credentials
#define DEVICE_UID "SMART_IOT_1X"         // Define the unique identifier for the device
#define HOST_URL "https://smartagri-41ab6-default-rtdb.asia-southeast1.firebasedatabase.app"  
#define TOKEN ""         // Define the unique identifier for the device

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

#define SEND "f2f9a4de-ef95-4fe1-9c2e-ab5ef6f0d6e9"
#define SEND_STRING "9e8fafe1-8966-4276-a3a3-d0b00269541e"

#define RECIVE "1450dbb0-e48c-4495-ae90-5ff53327ede4"
#define RECIVE_STRING "9393c756-78ea-4629-a53e-52fb10f9a63f"

#define DEEP_SLEEP_TIME  20 * 60 * 1000  // 15 minutes in millisecond

#define UPDATE_INTRAVEL 1 * 60 * 1000 // 5 minutes in millisecond
#define DEBUG_MODE true

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  15 * 60     /* Time ESP32 will go to sleep (in seconds) */


#endif

