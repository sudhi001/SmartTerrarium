#include "FirebaseHandler.h"
#include "addons/TokenHelper.h"

/**
 * @brief Default constructor for the FirebaseHandler class.
 *
 * This constructor initializes the member variables of the class with default values.
 */

FirebaseHandler::FirebaseHandler( )
    : isAuthenticated(false), elapsedMillis(0), update_interval(10000)
{
}

/**
 * @brief Initializes the Firebase connection with the provided API key and database URL.
 *
 * This method attempts to sign up a new user and sets the `isAuthenticated` flag accordingly. It also configures the Firebase library and starts the connection.
 *
 * @param apiKey The Firebase API key.
 * @param databaseUrl The Firebase database URL.
 */
bool FirebaseHandler::connect(AppStorage appStorage,String host,String token)
{
       this->appStorage = appStorage;
        config.api_key = token;
        config.database_url = host;
        Firebase.reconnectWiFi(true);
        if (Firebase.signUp(&config, &auth, "", ""))
        {
            isAuthenticated = true;
            Serial.println("Firebase authentication successful");
            fuid = auth.token.uid.c_str();
        }
        else
        {
            Serial.println("Firebase authentication failed");
        }
        // Assign the callback function for the long running token generation task, see addons/TokenHelper.h
        config.token_status_callback = tokenStatusCallback;
        Firebase.begin(&config, &auth);
        Serial.println("Firebase initialized!");
        return true;
}

/**
 * @brief Uploads JSON data to the specified node in the Firebase database.
 *
 * This method checks if the connection is ready, the user is authenticated, and the update interval has elapsed before sending the provided JSON data.
 *
 * @param node The path to the node in the Firebase database where the data should be uploaded.
 * @param jsonstring The JSON string to be uploaded.
 *
 * @return true if the data upload was successful, false otherwise.
 */
bool FirebaseHandler::uploadData(const char *node, FirebaseJson json)
{

    Serial.println("Sending data to Firebase:");
    if (millis() - elapsedMillis > update_interval && isAuthenticated && Firebase.ready())
    {

        elapsedMillis = millis();
        if (Firebase.setJSON(fbdo, node, json))
        {
            Serial.println("Firebase data upload successful");
            return true;
        }
        else
        {
            Serial.println("Firebase data upload failed: ");
            Serial.print(fbdo.errorReason());
              Serial.println("Error---Completd");
            return false;
        }
    }
    else
    {
        Serial.println("Firebase is not ready or user is not authenticated");
        return false;
    }
}
