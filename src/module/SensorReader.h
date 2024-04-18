#ifndef SENSORREADER_H
#define SENSORREADER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DHT.h>

/**
 * @brief A class for reading sensor data from an RS485 sensor module.
 *
 * This class provides methods to communicate with an RS485 sensor module 
 * and read various environmental parameters like moisture, temperature, 
 * and potentially other sensor-specific values (depending on the sensor model).
 */
class SensorReader {
public:
  /**
   * @brief Constructor for the SensorReader class.
   *
   * This constructor initializes a SoftwareSerial object for communication 
   * with the sensor and sets the baud rate.
   *
   * @param rxPin The receive pin connected to the RS485 sensor module.
   * @param txPin The transmit pin connected to the RS485 sensor module.
   */
  SensorReader(int rxPin, int txPin,int dhtPin, uint8_t dhtType);

  void begin();

  /**
   * @brief Reads the moisture level from the sensor and returns a byte value.
   *
   * This method sends a specific command to the sensor to retrieve the 
   * moisture level data and returns the received byte value (interpretation 
   * might require sensor-specific knowledge).
   *
   * @return The moisture level as a int value.
   */
  int readMoisture();

  /**
   * @brief Reads the temperature from the sensor and returns an integer value.
   *
   * This method sends a specific command to the sensor to retrieve the 
   * temperature data and returns the received two bytes combined as an integer 
   * (interpretation might require sensor-specific knowledge).
   *
   * @return The temperature as an integer value.
   */
  int readTemperature();

  int readAtmosphericTemperature();

  int readAtmosphericHumidity();

  /**
   * @brief Reads the electrical conductivity (EC) from the sensor and returns a byte value.
   *
   * This method assumes the sensor supports EC measurement and sends a 
   * specific command to retrieve the data. It returns the received byte value 
   * (interpretation might require sensor-specific knowledge).
   *
   * @return The electrical conductivity as a byte value (if supported).
   */
  byte readEconduc();

  /**
   * @brief Reads the pH level from the sensor and returns a byte value.
   *
   * This method assumes the sensor supports pH measurement and sends a 
   * specific command to retrieve the data. It returns the received byte value 
   * (interpretation might require sensor-specific knowledge).
   *
   * @return The pH level as a int value (if supported).
   */
  int readPh();

  /**
   * @brief Reads the nitrogen level from the sensor and returns a byte value.
   *
   * This method assumes the sensor supports nitrogen measurement and sends a 
   * specific command to retrieve the data. It returns the received byte value 
   * (interpretation might require sensor-specific knowledge).
   *
   * @return The nitrogen level as a byte value (if supported).
   */
  byte readNitrogen();

  /**
   * @brief Reads the phosphorous level from the sensor and returns a byte value.
   *
   * This method assumes the sensor supports phosphorous measurement and sends a 
   * specific command to retrieve the data. It returns the received byte value 
   * (interpretation might require sensor-specific knowledge).
   *
   * @return The phosphorous level as a byte value (if supported).
   */
  byte readPhosphorous();

  /**
   * @brief Reads the potassium level from the sensor and returns a byte value.
   *
   * This method assumes the sensor supports potassium measurement and sends a 
   * specific command to retrieve the data. It returns the received byte value 
   * (interpretation might require sensor-specific knowledge).
   *
   * @return The potassium level as a byte value (if supported).
   */
  byte readPotassium();

private:
  /**
   * @brief SoftwareSerial object for communication with the RS485 sensor module.
   */
  SoftwareSerial softwareSerial;
  DHT dht;
};

#endif
