#include "ModuleController.h"
#include "utils/Logger.h"


ModuleController::ModuleController(int waterPin, int sprayPin)
{
    this->sprayPin = sprayPin;
    this->waterPin = sprayPin;
    isSprayModuleOn = false;
    isWaterModuleOn = false;
}

void ModuleController::begin(){
  pinMode(this->sprayPin, OUTPUT); // Spray module
  pinMode(this->waterPin, OUTPUT);// Water module
  deactivateSprayModule();
  deactivateWaterMotor();
}
void ModuleController::activateSprayModule() {
  digitalWrite(this->sprayPin, LOW);
  Logger::log("Spray module activated");
  isSprayModuleOn = true;
  delay(2000);
  digitalWrite(this->sprayPin, HIGH);
   isSprayModuleOn = false;
  Logger::log("Spray module deactivated after 2 seconds");
}

void ModuleController::deactivateSprayModule() {
  digitalWrite(this->sprayPin, HIGH);
   isSprayModuleOn = false;
  Logger::log("Spray module deactivated");
}

void ModuleController::activateWaterMotor() {
  digitalWrite(this->waterPin, LOW);
  Logger::log("Water motor activated");
  isWaterModuleOn = true;
  delay(2000);
  digitalWrite(this->waterPin, HIGH);
   isWaterModuleOn = false;
  Logger::log("Water motor deactivated after 2 seconds");
}

void ModuleController::deactivateWaterMotor() {
  digitalWrite(this->waterPin, HIGH);
   isWaterModuleOn = false;
  Logger::log("Water motor module deactivated");
}
