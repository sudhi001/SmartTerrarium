#include "SensorReader.h"

SensorReader::SensorReader(int rxPin, int txPin,int dhtPin, uint8_t dhtType):softwareSerial(rxPin, txPin), dht(dhtPin, dhtType)
{
     
    softwareSerial.begin(9600);
}
void SensorReader::begin()
{
      softwareSerial.begin(9600); 
      dht.begin(); 
}
int SensorReader::readMoisture()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0F};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return values[4]/ 1.8;
}

byte SensorReader::readEconduc()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xce};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return values[4];
}

int SensorReader::readTemperature()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x13, 0x00, 0x01, 0x75, 0xcf};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return ((values[3] << 8) | values[4]) / 10.0;
}

int SensorReader::readAtmosphericTemperature()
{
    return dht.readTemperature();
}
int SensorReader::readAtmosphericHumidity()
{
    return dht.readHumidity();
}


int SensorReader::readPh()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0b};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return values[4]/ 25;
}

byte SensorReader::readNitrogen()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return values[4];
}

byte SensorReader::readPhosphorous()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return values[4];
}

byte SensorReader::readPotassium()
{
    const byte command[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
    softwareSerial.write(command, sizeof(command));
    delay(200);
    byte values[7];
    softwareSerial.readBytes(values, 7);
    return values[4];
}
