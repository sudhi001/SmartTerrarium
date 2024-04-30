#include "network/firebase/FirebaseHandler.h"
#include "module/ModuleController.h"
#include "module/SensorReader.h"
#include "network/NetworkController.h"
#include "network/BLEServerController.h"

class Application
{

private:
    FirebaseHandler firebaseHandler;
    NetworkController networkController;
    ModuleController moduleController;
    BLEServerController bleServerController;
    SensorReader sensorReader;
    bool isConnected = false;

public:
    // Constructor to initialize members with appropriate parameters
    Application(
        int waterMotorPin, int sprayPin,
        int rxPin, int txPin, int dhtPin, uint8_t dhtType)
        : moduleController(waterMotorPin, sprayPin),
          sensorReader(rxPin, txPin, dhtPin, dhtType)
    {
    }

    void begin()
    {
        bleServerController.connect();
        AppStorage *storage = bleServerController.getAppStorage();
        isConnected = networkController.connect(storage);

        sensorReader.begin();
        moduleController.begin();
        if (isConnected)
        {
            firebaseHandler.connect();
        }
    }

    void run()
    {

        firebaseHandler.createSensorObjet(&bleServerController, &sensorReader, &moduleController);
        bleServerController.run();
    }
};