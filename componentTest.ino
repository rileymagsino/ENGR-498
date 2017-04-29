#include <SPI.h>
#include "Adafruit_MAX31855.h"

Adafruit_MAX31855 thermocouple1(8, 7, 6); // initialize thermocouple 1 for Micro     TRUMP (SAMECLK, SAMECS, DIFFDO)
Adafruit_MAX31855 thermocouple2(8, 7, 5); // initialize thermocouple 2 for Micro     TRUMP (SAMECLK, SAMECS, DIFFDO)

  int chamber1O [] = {11, 13, 12}; // pump, solenoid valve, heater
  int chamber2O [] = {11, 2, 4}; // pump, solenoid valve, heater
  int compCountO = 3;
void setup() {
  // put your setup code here, to run once:
for (int p = 0; p < compCountO; p++) { // Set pins to OUTPUT      TRUMP
    pinMode(chamber1O[p], OUTPUT); //      TRUMP
    pinMode(chamber2O[p], OUTPUT); //     TRUMP
  }
}

void loop() {
  analogWrite(chamber1O[1], 255); // solenoid valve is energized to 5V
  delay(1000*2);
  analogWrite(chamber1O[2], 255); // heater turns on
  delay(1000*2);
  analogWrite(chamber1O[0], 228); // pump turns on
  delay(10000); // 20s delay
  
  analogWrite (chamber1O[2], 0); // heater turns off
  delay(1000*2);
  analogWrite(chamber1O[0], 0); // pump turns off
  delay(1000*2);
  analogWrite(chamber1O[1],0); // solenoid turns off
 
  delay(10000); // 20s delay

  digitalWrite(chamber2O[1], HIGH); // solenoid valve is energized to 5V
  delay(1000*2);
  analogWrite(chamber2O[2], 255); // heating turns on
  delay(1000*2);
  analogWrite(chamber2O[0], 228); // pump turns on
  delay(10000); // 20s delay
  
  analogWrite(chamber2O[2],0); // heater turns off
  delay(1000*2);
  analogWrite(chamber2O[0],0); // pump turns off
  delay(1000*2);
  analogWrite(chamber2O[1], 0); // solenoid turns off
  delay(10000); // 1hr delay
}
