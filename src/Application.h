#ifndef APPLICATION_H
#define APPLICATION_H

#include "public/FirebaseHandler.h"
#include "public/ModuleController.h"
#include "public/SensorReader.h"
#include "public/NetworkController.h"
#include "public/BLEServerController.h"

/**
 * @brief The Application class that initializes and coordinates various modules.
 */
class Application {
private:
    FirebaseHandler firebaseHandler;
    NetworkController networkController;
    ModuleController moduleController;
    BLEServerController bleServerController;
    SensorReader sensorReader;
    bool isConnected = false;

public:
    /**
     * @brief Constructor to initialize members with appropriate parameters.
     * 
     * @param waterMotorPin Pin for water motor.
     * @param sprayPin Pin for spray.
     * @param rxPin RX pin for sensor.
     * @param txPin TX pin for sensor.
     * @param dhtPin Pin for DHT sensor.
     * @param dhtType Type of DHT sensor.
     */
    Application(int waterMotorPin, int sprayPin, int rxPin, int txPin, int dhtPin, uint8_t dhtType);

    /**
     * @brief Initializes the application, connecting to BLE and network, and starting sensors and modules.
     */
    void begin();

    /**
     * @brief Runs the main application loop, updating sensors and modules, and handling BLE communication.
     */
    void run();
};

#endif // APPLICATION_H

