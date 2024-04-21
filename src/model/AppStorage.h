#ifndef APPSTORAGE_H
#define APPSTORAGE_H

struct AppStorage
{
  char ssid[64];
  char password[64];
  char apiKey[122];
  char deviceId[64];
  float sprayModuleActivateValue;
  float waterModuleActivateValue;
};


#endif
