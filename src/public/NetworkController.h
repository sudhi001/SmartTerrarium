#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

#include "model/AppStorage.h"
#include "config.h"
#include "public/Logger.h"

/**
 * @brief Class to manage network connections.
 * 
 * This class provides methods to connect to a WiFi network using credentials
 * stored in an AppStorage object. It includes functionality to check the SSID
 * and password, log network connection status, and manage WiFi connections.
 */
class NetworkController {
public:
    /**
     * @brief Connect to a WiFi network.
     * 
     * This method attempts to connect to a WiFi network using the SSID and
     * password stored in the provided AppStorage object. It logs the process
     * and handles disconnections and reconnections as needed.
     * 
     * @param appStorage Pointer to an AppStorage object containing network credentials.
     * @return true if connected successfully, false otherwise.
     */
    bool connect(AppStorage *appStorage);

private:
    /**
     * @brief Check if the SSID is valid.
     * 
     * This method checks if the SSID stored in the AppStorage object is valid (non-empty).
     * 
     * @param appStorage Pointer to an AppStorage object containing the SSID.
     * @return true if the SSID is valid, false otherwise.
     */
    bool checkSSID(AppStorage *appStorage);

    /**
     * @brief Check if the password is valid.
     * 
     * This method checks if the password stored in the AppStorage object is valid (non-empty).
     * 
     * @param appStorage Pointer to an AppStorage object containing the password.
     * @return true if the password is valid, false otherwise.
     */
    bool checkPassword(AppStorage *appStorage);

    /**
     * @brief Log the SSID and password status.
     * 
     * This method logs whether the SSID and password are valid.
     * 
     * @param isSSID true if the SSID is valid, false otherwise.
     * @param isPassword true if the password is valid, false otherwise.
     */
    void logSSIDAndPassword(bool isSSID, bool isPassword);

    /**
     * @brief Disconnect from the current WiFi network.
     * 
     * This method disconnects from the current WiFi network and cleans up the connection.
     */
    void disconnectFromWiFi();

    /**
     * @brief Connect to a WiFi network using provided credentials.
     * 
     * This method initiates a connection to a WiFi network using the SSID and
     * password stored in the AppStorage object. It logs the connection status.
     * 
     * @param appStorage Pointer to an AppStorage object containing network credentials.
     */
    void connectToWiFi(AppStorage *appStorage);
};

#endif // NETWORK_CONTROLLER_H
