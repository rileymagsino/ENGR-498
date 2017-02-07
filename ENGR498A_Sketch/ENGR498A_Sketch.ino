
#include <SPI.h>
#include "Adafruit_MAX31855.h"


int chamber1I [] = {0,1,2}; // thermocouple data
int chamber1O [] = {A5,A1,A6}; // pump, solenoid valve, heater
int chamber2I [] = {3,5,6}; // thermocouple data
int chamber2O [] = {A5,A0,11}; // pump, solenoid valve, heater
int compCountI = 3;
int compCountO = 3;

int T1 = 300; // arbitrary time constant (for now)
  
void setup() {
  // put your setup code here, to run once:
for (int p = 0; p < compCountI; p++) { // Set pins to INPUT
  pinMode(chamber1I[p], INPUT);
  pinMode(chamber2I[p], INPUT); 
}

for (int p = 0; p < compCountO; p++) {
  pinMode(chamber1O[p],OUTPUT);
  pinMode(chamber2O[p], OUTPUT);
  }
}

void loop() {
    int pumpTimer = 0;
Adafruit_MAX31855 thermocouple(0,1,2); // initialize thermocouple 1
while (pumpTimer < T1){ // Time Constraint 1  
   Serial.println(thermocouple.readInternal()); // prints data into text
   double c = thermocouple.readFarenheit(); // thermocouple converts data to F
   
   analogWrite(chamber2O[1], HIGH); // solenoid valve is energized (may need to use PWM to get down to 3.3 V after 50 ms
   delay(50); // delays for 50 ms
   analogWrite(chamber2O[1], 169); // solenoid valve supplied with 3.3V
   
   if (c > 210) { // stays the same
     analogWrite(chamber1O[2], LOW); // turns heater off in CHAMBER1
     }     
   
   if (c < 200) {
    analogWrite(chamber1O[2], HIGH); // turns heater on in CHAMBER1
   }

   if (c < 170) {
    analogWrite(chamber1O[0], LOW); // turns pump off in CHAMBER1
   }

   if (c > 205) {
    analogWrite(chamber1O[0], HIGH); // turns pump on in CHAMBER1
   }
   while ( c > 205 ) {
    pumpTimer = pumpTimer++;
   }
//possible code for interrupt???
}
  pumpTimer = 0; // reset counter
  delay(1000*60*720); // 1000 ms * 60s * 720 min (12 hour delay)
  
while(pumpTimer < T1) { // Time Constraint 1
   Adafruit_MAX31855 thermocouple(3,5,6); // initialize thermocouple 2
   Serial.println(thermocouple.readInternal()); // prints data into text
   double c = thermocouple.readFarenheit(); // thermocouple converts data to F
   
   analogWrite(chamber2O[1], HIGH); // solenoid valve is energized (may need to use PWM to get down to 3.3 V after 50 ms
   delay(50); // delays for 50 ms
   analogWrite(chamber2O[1], 169); // solenoid valve supplied with 3.3V
   
   if (c > 210) {
     analogWrite(chamber2O[2], LOW); // turns heater off in CHAMBER1
     }     
   
   if (c < 200) {
     analogWrite(chamber2O[2], HIGH); // turns heater on in CHAMBER1
     }

   if (c > 170) {
     analogWrite(chamber2O[0], LOW); // turns pump off in CHAMBER1
   }

   if (c > 205) {
     analogWrite(chamber2O[0], HIGH); // turns pump on in CHAMBER1
   }  

    while ( c > 205 ) {
    pumpTimer = pumpTimer++;
   }
   
  //possible code for interrupt??? ( in case pump never turns on )
}

}
