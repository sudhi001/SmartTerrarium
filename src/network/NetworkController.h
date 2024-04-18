#ifndef NETWORKCONTRLLER_H
#define NETWORKCONTRLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>


class NetworkController {
public:

  NetworkController(String ssid, String password);

  void begin();


private:
   String ssid;
   String password;

};

#endif
