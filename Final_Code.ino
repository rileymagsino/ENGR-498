#include <SPI.h>
#include "Adafruit_MAX31855.h"

Adafruit_MAX31855 thermocouple1(8, 7, 6); // initialize thermocouple 1 for Micro     TRUMP (SAMECLK, SAMECS, DIFFDO)
Adafruit_MAX31855 thermocouple2(8, 7, 5); // initialize thermocouple 2 for Micro     TRUMP (SAMECLK, SAMECS, DIFFDO)

// Pin Layout for Arduino Micro
int chamber1O [] = {11, 13, 12}; // pump, solenoid valve, heater
int chamber2O [] = {11, 2, 4}; // pump, solenoid valve, heater
int compCountO = 3;
int cycle = 0;

extern volatile unsigned long timer0_millis; // internal timer
unsigned long new_value = 0; // internal timer value when 24 hours is reached

void setup() { //     TRUMP
  for (int p = 0; p < compCountO; p++) { // Set pins to OUTPUT      TRUMP
    pinMode(chamber1O[p], OUTPUT); //      TRUMP
    pinMode(chamber2O[p], OUTPUT); //     TRUMP
  }
}

void loop() {
  long delay1 = 43200000L; // 12hr constant (changed to long since int couldnt hold enough data, int has a range of 32767 while long has range of 2,147,483,647) 1000*60*60*12
  long delay2 = 50400000L; // 14hr constant 1000*60*60*14
  long delay3 = 7200000L; // 2hr delay constant
  long runTime = millis(); 
  int cycle = 0;
  double f = thermocouple1.readFarenheit();
  
  if ((runTime >= 0) && (cycle = 0) && (f < 140)){ // immediately turn on
  analogWrite(chamber1O[1], 255); // solenoid valve A is energized
  delay(2000);
  analogWrite(chamber1O[2], 255); // turns heater A on in CHAMBER1
  delay(2000);
  analogWrite(chamber1O[0], 200); // turns pump A on in CHAMBER1 with 4V
  cycle = 1; 
  }
  
  if ((runTime >= 0) && (f > 210) && (cycle = 1)) {
    analogWrite(chamber1O[2], 0); // turns heater A off in CHAMBER1
  }

  if ((runTime >= 0) && (f < 200) && (cycle = 1)) {
    analogWrite(chamber1O[2], 0); // turns heater A off in CHAMBER1
  }

  if ((runTime >= 0) && (f > 205) && (cycle = 1)) {
    analogWrite(chamber1O[0], 0); // turns heater A off in CHAMBER1
  }

  if ((runTime >= 0) && (f < 170) && (cycle = 1)) {
    analogWrite(chamber1O[0], 200); // turns pump off in CHAMBER1
  }

  if ((runTime >= delay3) && (cycle = 1)) { // two hours passed
  analogWrite(chamber1O[2], 0); // turn Heater A off
  delay(1800000L); // 1000ms/s * 60s/min * 30 min => 30 min
  analogWrite(chamber1O[1], 0); // pump off
  delay(2000);
  analogWrite(chamber1O[0], 0); // solenoid valve A off
  cycle = 2;
  }
  
  if ((runTime >= delay2) && (cycle = 2) && (f < 140)) { // 14 hours have passed
  analogWrite(chamber2O[1], 255); // solenoid valve B is energized
  delay(2000);
  analogWrite(chamber2O[2], 255); // turns heater B on in CHAMBER1
  delay(2000);
  analogWrite(chamber2O[0], 200); // turns pump B on in CHAMBER1 with 4V 
  cycle = 3;
 }
  
  if ((runTime >= 57600000L) && (cycle = 3)) { // 16 hours have passed
  analogWrite(chamber2O[2], 0); // turn Heater A off
  delay(delay3); // 1000ms/s * 60s/min * 30 min => 30 min
  analogWrite(chamber2O[1], 0); // pump off
  delay(2000);
  analogWrite(chamber2O[0], 0); // solenoid valve A off
}

  if ((runTime >= 86400000L) && (cycle = 3)) { // timer returns to 0 after one full day
  cycle = 0;
  setMillis(new_value);
  }
}

void setMillis(unsigned long new_millis) // resets internal clock to 0
{
  uint8_t oldSREG = SREG;
 
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
