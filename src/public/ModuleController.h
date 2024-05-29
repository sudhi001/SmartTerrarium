#ifndef MODULECONTROLLER_H
#define MODULECONTROLLER_H

#include <Arduino.h>  // Assuming Arduino environment

/**
 * @brief A class for controlling modules like sprayers and water motors in an Arduino project.
 */
class ModuleController {
public:
    bool isSprayModuleOn ;
    bool isWaterModuleOn ;

      /**
   *
   * @param waterPin The Arduino pin connected to the water motor.
   * @param sprayPin The Arduino pin connected to the spray module.
   */

   ModuleController(int waterPin, int sprayPin);

   void begin();
  /**
   * @brief Activates a spray module connected to the specified pin.
   *
   * This method turns the spray module on  for 2 seconds, then turns it off .
   *
   */
  void activateSprayModule();

  /**
   * @brief Deactivates a spray module connected to the specified pin.
   *
   * This method turns the spray module off .
   *
   */
  void deactivateSprayModule();

  /**
   * @brief Activates a water motor connected to the specified pin.
   *
   * This method turns the water motor on for 2 seconds, then turns it off .
   * 
   */
  void activateWaterMotor();

  /**
   * @brief Deactivates a water motor connected to the specified pin.
   *
   * This method turns the water motor off .
   *
   */
  void deactivateWaterMotor();

private:
    int waterPin;
    int sprayPin;
};

#endif
