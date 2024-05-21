#ifndef FIREBASEHANDLER_H
#define FIREBASEHANDLER_H

#include <FirebaseESP32.h> // Include Firebase library
#include "network/BLEServerController.h"
#include "module/SensorReader.h"
#include "module/ModuleController.h"

/**
 * @brief A class for handling interaction with a Firebase Realtime Database from an Arduino board.
 *
 * This class provides methods for initializing the Firebase connection,
 * authenticating with Firebase, and uploading JSON data to the database.
 */
class FirebaseHandler
{
public:
  void createSensorObjet(BLEServerController *bleCtr, SensorReader *sensorReader, ModuleController *moduleController);
  /**
   * @brief Stores the Firebase user ID (empty string initially).
   */
  String fuid;

  FirebaseHandler();

  /**
   * @brief Initializes the Firebase connection with the provided API key and database URL.
   *
   * This method attempts to sign up a new user and sets the `isAuthenticated` flag accordingly. It also configures the Firebase library and starts the connection.
   *
   */
  void connect();

  /**
   * @brief Uploads JSON data to the specified node in the Firebase database.
   *
   * This method checks if the connection is ready, the user is authenticated, and the update interval has elapsed before sending the provided JSON data.
   *
   * @param node The path to the node in the Firebase database where the data should be uploaded.
   *
   * @return true if the data upload was successful, false otherwise.
   */
  void uploadData();

private:
  String sensorPath;
  bool isConnected;
  FirebaseJson sensor_json;
   bool isSensorDataAvailable; 
  /**
   * @brief Firebase data object used for storing data to be uploaded.
   */
  FirebaseData fbdo;

  /**
   * @brief Firebase authentication object for managing user authentication.
   */
  FirebaseAuth auth;

  /**
   * @brief Firebase configuration object to hold Firebase configuration details.
   */
  FirebaseConfig config;

  /**
   * @brief Boolean flag indicating authentication status.
   */
  bool isAuthenticated;




};

#endif