#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "config.h"

/**
 * @brief A simple logging class for Arduino with conditional debug mode.
 * 
 * This class provides static methods to log messages to the Serial monitor.
 * Logging can be enabled or disabled by setting the DEBUG_MODE flag.
 */

class Logger {
public:

/**
     * @brief Log a message to the Serial monitor.
     * 
     * This method logs the provided message to the Serial monitor if DEBUG_MODE is true.
     * 
     * @param message The message to be logged.
     */
    static void log(const String& message) {
        if (DEBUG_MODE) {
            Serial.println(message);
        }
    }

   /**
 * @brief Log a message and a boolean value to the Serial monitor.
 * 
 * This method logs the provided message and boolean value to the Serial monitor if DEBUG_MODE is true.
 * 
 * @param message The message to be logged.
 * @param data The boolean value to be logged.
 */
static void log(const String& message, const bool& data) {
    if (DEBUG_MODE) {
        Serial.print(message);
        Serial.print(": ");
        Serial.println(data ? "true" : "false");
    }
}
   /**
 * @brief Log a message and a boolean value to the Serial monitor.
 * 
 * This method logs the provided message and boolean value to the Serial monitor if DEBUG_MODE is true.
 * 
 * @param message The message to be logged.
 * @param data The String value to be logged.
 */
static void log(const String& message, const String& data) {
    if (DEBUG_MODE) {
        Serial.print(message);
        Serial.print(": ");
        Serial.println(data);
    }
}

   static void logp(const String& message) {
        if (DEBUG_MODE) {
            Serial.print(message);
        }
    }
};

#endif