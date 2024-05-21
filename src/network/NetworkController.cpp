#include <WiFi.h>
#include "NetworkController.h"


bool NetworkController::connect(AppStorage *appStorage) {
    bool isSSID = checkSSID(appStorage);
    bool isPassword = checkPassword(appStorage);
    logSSIDAndPassword(isSSID, isPassword);

    if (isSSID && isPassword) {
        disconnectFromWiFi();
        connectToWiFi(appStorage);
        return true;
    }
    return false;
}

bool NetworkController::checkSSID(AppStorage *appStorage) {
    return strlen(appStorage->ssid) > 0;
}

bool NetworkController::checkPassword(AppStorage *appStorage) {
    return strlen(appStorage->password) > 0;
}

void NetworkController::logSSIDAndPassword(bool isSSID, bool isPassword) {
    Logger::log("Is Password Exists", isPassword);
    Logger::log("Is SSID Exists", isSSID);
}

void NetworkController::disconnectFromWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        Logger::log("Disconnecting from current Wi-Fi network...");
        WiFi.disconnect(true); // Disconnect and clean up
        delay(1000);           // Wait for disconnection
    }
}

void NetworkController::connectToWiFi(AppStorage *appStorage) {
    WiFi.begin(appStorage->ssid, appStorage->password);
    Logger::log("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Logger::logp(".");
        delay(300);
    }
    Logger::log("Connected with IP", WiFi.localIP().toString());
}
