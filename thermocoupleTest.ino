#include <SPI.h>
#include "Adafruit_MAX31855.h"

Adafruit_MAX31855 thermocouple1(8, 7, 6); // initialize thermocouple 1 for Micro     TRUMP (SAMECLK, SAMECS, DIFFDO)
Adafruit_MAX31855 thermocouple2(8, 7, 5); // initialize thermocouple 2 for Micro     TRUMP (SAMECLK, SAMECS, DIFFDO)

// Pin Layout for Arduino Micro
int chamber1O [] = {11, 13, 12}; // pump, solenoid valve, heater
int chamber2O [] = {11, 3, 4}; // pump, solenoid valve, heater
int compCountO = 3;
int cycle = 0;

void setup() { //     TRUMP
//  Serial.begin(9600);
  for (int p = 0; p < compCountO; p++) { // Set pins to OUTPUT      TRUMP
    pinMode(chamber1O[p], OUTPUT); //      TRUMP
    pinMode(chamber2O[p], OUTPUT); //     TRUMP
  }
}

void loop() {
  double f = thermocouple1.readFarenheit(); // thermocouple converts data to F and stores value into c      TRUMP  
  Serial.print(f);
  Serial.println();
  analogWrite(chamber2O[2], 255); // turns heater on in CHAMBER1
  if ( f > 100 ) {
  analogWrite(chamber2O[2], 0); // 
  delay(1000*20); // delays for 20 s
  }  
}


