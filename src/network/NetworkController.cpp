#include "NetworkController.h"
#include <WiFi.h>
#include <EEPROM.h>
#include <FirebaseESP32.h>
void NetworkController::handleReport()
{
    Serial.println("Handle Report");
  webServer.send(200, "application/json", sensorData);
}
void NetworkController::printStorage()
{
  Serial.println("Network Credentials:");
  Serial.print("SSID: ");
  Serial.println(String(appStorage.ssid));
  Serial.print("Password: ");
  Serial.println(String(appStorage.password));
  Serial.print("APIKey: ");
  Serial.println(String(appStorage.apiKey));
  Serial.print("deviceId: ");
  Serial.println(String(appStorage.deviceId));
}
void NetworkController::handleReset()
{
  FirebaseJson sensor_json;
  clearStorage();
  sensor_json.add("status", "SUCCESS");
  String jsonStr;
  sensor_json.toString(jsonStr, true);
  Serial.println(jsonStr);
  webServer.send(200, "application/json", jsonStr);
  connect();
}

void NetworkController::handleSettings()
{
  FirebaseJson sensor_json;
  sensor_json.add("status", "SUCCESS");
  sensor_json.add("deviceUniqueId", "test");
  String jsonStr;
  sensor_json.toString(jsonStr, true);
  Serial.println(jsonStr);
  webServer.send(200, "application/json", jsonStr);
}

void NetworkController::handleNetworkConfig()
{
  FirebaseJson response_json;
  if (webServer.hasArg("plain") == false)
  {
    response_json.add("status", "ERROR");
    response_json.add("message", "Unsupported");
    String jsonStr;
    response_json.toString(jsonStr, true);
    Serial.println(jsonStr);
    webServer.send(200, "application/json", jsonStr);
  }
  else
  {
    String body = webServer.arg("plain");
    FirebaseJson requestJson;
    requestJson.setJsonData(body);
    String jsonStr;
    response_json.add("status", "SUCCESS");
    FirebaseJsonData ssidResult;
    requestJson.get(ssidResult, "ssid");
    FirebaseJsonData passwordResult;
    requestJson.get(passwordResult, "password");

    FirebaseJsonData tokenyResult;
    requestJson.get(tokenyResult, "token");

    FirebaseJsonData deviceIdResult;
    requestJson.get(deviceIdResult, "deviceId");

    // Copy String values to char arrays and store in EEPROM
    String ssidValue = ssidResult.stringValue;
    String passwordValue = passwordResult.stringValue;
    String apiValue = tokenyResult.stringValue;
    String deviceIdValue = deviceIdResult.stringValue;

    ssidValue.toCharArray(appStorage.ssid, sizeof(appStorage.ssid));
    passwordValue.toCharArray(appStorage.password, sizeof(appStorage.password));
    apiValue.toCharArray(appStorage.apiKey, sizeof(appStorage.apiKey));
    deviceIdValue.toCharArray(appStorage.deviceId, sizeof(appStorage.deviceId));

    // Ensure null termination
    appStorage.ssid[sizeof(appStorage.ssid) - 1] = '\0';
    appStorage.password[sizeof(appStorage.password) - 1] = '\0';
    appStorage.apiKey[sizeof(appStorage.apiKey) - 1] = '\0';
    appStorage.deviceId[sizeof(appStorage.deviceId) - 1] = '\0';
    appStorage.sprayModuleActivateValue = 27;
    appStorage.waterModuleActivateValue = 15;

    // Write to EEPROM
    EEPROM.begin(sizeof(AppStorage)); // Initialize EEPROM with struct size
    EEPROM.put(0, appStorage);        // Store the struct at address 0
    EEPROM.commit();                  // Commit the data to EEPROM
    EEPROM.end();                     // Release EEPROM resources
    response_json.add("ssid", ssidResult.stringValue);
    response_json.toString(jsonStr, true);
    Serial.println(jsonStr);
    // Print the ssid and password using Serial.println()
    printStorage();
    webServer.send(200, "application/json", jsonStr);
     connect();
  }
}
void NetworkController::clearStorage()
{

  String empty = "";
  empty.toCharArray(appStorage.ssid, sizeof(appStorage.ssid));
  empty.toCharArray(appStorage.password, sizeof(appStorage.password));
  empty.toCharArray(appStorage.apiKey, sizeof(appStorage.apiKey));
  empty.toCharArray(appStorage.deviceId, sizeof(appStorage.deviceId));

  // Ensure null termination
  appStorage.ssid[sizeof(appStorage.ssid) - 1] = '\0';
  appStorage.password[sizeof(appStorage.password) - 1] = '\0';
  appStorage.apiKey[sizeof(appStorage.apiKey) - 1] = '\0';
  appStorage.deviceId[sizeof(appStorage.deviceId) - 1] = '\0';
  // Set default values for float fields
  appStorage.sprayModuleActivateValue = 0.0;
  appStorage.waterModuleActivateValue = 0.0;
  clearEEPROM();

  EEPROM.begin(sizeof(AppStorage));
  EEPROM.get(0, appStorage);
  EEPROM.end();
  printStorage();
}
void NetworkController::initializeAppStorage()
{

  //clearStorage();

  EEPROM.begin(sizeof(AppStorage));
  EEPROM.get(0, appStorage);
  EEPROM.end();
  printStorage();
}
void NetworkController::clearEEPROM()
{
  size_t storageSize = sizeof(AppStorage);
  EEPROM.begin(storageSize);
  for (int i = 0; i < storageSize; i++)
  {
    EEPROM.write(i, 0);
  }
  // Commit the changes to EEPROM
  EEPROM.commit();
  // End EEPROM usage
  EEPROM.end();
  Serial.println("EEPROM cleared successfully.");
  printStorage();
}
void NetworkController::handleSettingsConfig()
{
  FirebaseJson sensor_json;
  sensor_json.add("status", "SUCCESS");
  String jsonStr;
  sensor_json.toString(jsonStr, true);
  Serial.println(jsonStr);
  webServer.send(200, "application/json", jsonStr);
}
AppStorage NetworkController::getAppStorage()
{
  return appStorage;
}
void NetworkController::handleNotFound()
{
  FirebaseJson sensor_json;
  sensor_json.add("status", "ERROR");
  sensor_json.add("message", "Unknown URL");
  String jsonStr;
  sensor_json.toString(jsonStr, true);
  Serial.println(jsonStr);
  webServer.send(400, "application/json", jsonStr);
}

void NetworkController::startServer()
{
  Serial.println("Starting Server");
  webServer.on("/api/v1/report", [&]()
               { handleReport(); });
   webServer.on("/api/v1/reset", [&]()
               { handleReset(); });
  webServer.on("/api/v1/settings", [&]()
               { handleSettings(); });
  webServer.on("/api/v1/config/network", HTTP_POST, [&]()
               { handleNetworkConfig(); });
  webServer.on("/api/v1/config/settings", HTTP_POST, [&]()
               { handleSettingsConfig(); });
               
  webServer.onNotFound([&]()
                       { handleNotFound(); });
  webServer.begin();
  Serial.println("Server stated ");
  isWebServerRunning = true;
}

bool NetworkController::connect()
{
  if (isStorageEmpty())
  {
    IPAddress local_ip(192, 168, 0, 1);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    Serial.println("WiFi SSID is not configured");
    Serial.println("\n[*] Creating AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password, channel, hide_SSID, max_connection);
    Serial.print("[+] AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());
    startServer();
    return false;
  }
  else
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Disconnecting from current Wi-Fi network...");
      WiFi.disconnect(true); // Disconnect and clean up
      delay(1000);           // Wait for disconnection
    }

    WiFi.begin(appStorage.ssid, appStorage.password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    startServer();

    return true;
  }
}

bool NetworkController::run()
{
  webServer.handleClient();
  return isWebServerRunning;
}
bool NetworkController::isStorageEmpty()
{
  Serial.print("Length of SSID is ");
  Serial.print(strlen(appStorage.ssid));
  Serial.println(".");
  return (strlen(appStorage.ssid) == 0) && (strlen(appStorage.password) == 0);
}