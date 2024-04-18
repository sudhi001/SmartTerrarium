#include "ModuleController.h"


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
  Serial.println("Spray module activated");
  isSprayModuleOn = true;
  delay(2000);
  digitalWrite(this->sprayPin, HIGH);
   isSprayModuleOn = false;
  Serial.println("Spray module deactivated after 2 seconds");
}

void ModuleController::deactivateSprayModule() {
  digitalWrite(this->sprayPin, HIGH);
   isSprayModuleOn = false;
  Serial.println("Spray module deactivated");
}

void ModuleController::activateWaterMotor() {
  digitalWrite(this->waterPin, LOW);
  Serial.println("Water motor activated");
  isWaterModuleOn = true;
  delay(2000);
  digitalWrite(this->waterPin, HIGH);
   isWaterModuleOn = false;
  Serial.println("Water motor deactivated after 2 seconds");
}

void ModuleController::deactivateWaterMotor() {
  digitalWrite(this->waterPin, HIGH);
   isWaterModuleOn = false;
  Serial.println("Water motor module deactivated");
}
