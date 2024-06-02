#include "Application.h"

Application::Application(int waterMotorPin, int sprayPin, int rxPin, int txPin, int dhtPin, uint8_t dhtType)
    : moduleController(waterMotorPin, sprayPin),
      sensorReader(rxPin, txPin, dhtPin, dhtType) {}

void Application::begin() {
    // Connect to BLE server
    bleServerController.connect();

    // Retrieve stored network credentials
    AppStorage *storage = bleServerController.getAppStorage();

    // Connect to the network
    isConnected = networkController.connect(storage);
      // Connect to Firebase if network connection is successful
    if (isConnected) {
        firebaseHandler.connect();
    }

    // Initialize sensor reader and module controller
    sensorReader.begin();
    moduleController.begin();

  
}

void Application::run() {
    // Create sensor data object
    firebaseHandler.createSensorObjet(&bleServerController, &sensorReader, &moduleController);

    // Run BLE server tasks
    bleServerController.run();
}
