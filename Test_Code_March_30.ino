
#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define T1 300
// Pin Layout for Arduino Micro
int chamber1I [] = {6,3,5}; // thermocouple data
int chamber1O [] = {A5,A1,4}; // pump, solenoid valve, heater
int chamber2I [] = {0,0,0}; // thermocouple data UPDATE WHEN OTHER THREMOCOUPLE COMES IN ASAP
int chamber2O [] = {A5,A0,11}; // pump, solenoid valve, heater
int compCountI = 3;
int compCountO = 3; 
// Only one thermocouple at the moment
// PinLayout for Arduino Pro Trinket
//int chamber1I [] = {0,1,3}; // thermocouple data (MAXCLK, MAXCS, MAXDO)
//int chamber1O [] = {A5,A1,4}; // pump, solenoid valve, heater
//int chamber2I [] = {0,5,3}; // thermocouple data (MAXCLK, MAXCS, MAXDO)
//int chamber2O [] = {A5,A0,11}; // pump, solenoid valve, heater
//int compCountI = 3;
//int compCountO = 3;
//int T1 = 300; // arbitrary time constant (for now) 
  
void setup() { //     TRUMP
for (int p = 0; p < compCountI; p++) { // Set pins to INPUT     TRUMP
  pinMode(chamber1I[p], INPUT); //      TRUMP
  pinMode(chamber2I[p], INPUT); //      TRUMP
}

for (int p = 0; p < compCountO; p++) { // Set pins to OUTPUT      TRUMP
  pinMode(chamber1O[p],OUTPUT); //      TRUMP
  pinMode(chamber2O[p], OUTPUT); //     TRUMP
  }
}

void loop() {
    int pumpTimer = 0; //initialize timer

while (pumpTimer < T1){ // Time Constraint 1
   Adafruit_MAX31855 thermocouple(chamber1I[0], chamber1I[1], chamber1I[2]); // initialize thermocouple 1 for Micro     TRUMP
   Serial.println(thermocouple.readInternal()); // prints data into text      TRUMP 
   double c = thermocouple.readFarenheit(); // thermocouple converts data to F and stores value into c      TRUMP
   Serial.print(c); // can be set to print for troubleshooting purposes TRUMP
   analogWrite(chamber2O[1], HIGH); // solenoid valve is energized to 5V
   delay(50); // delays for 50 ms
   analogWrite(chamber2O[1], 127); // solenoid valve supplied with 2.5V (CHANGE 127 TO 169 FOR 3.3 V)
   
   if (c > 210) { // temp. is too high    TRUMP
     analogWrite(chamber1O[2], LOW); // turns heater off in CHAMBER1      TRUMP
     }     
   
   if (c < 200) { //temp. is too low
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
}
    
//Stops cycling
  pumpTimer = 0; // reset counter

  for ( int i = 0; i < 3; i++) {
  chamber1O[i] == LOW; // Turns off pump/heater/solenoid valves in  Chamber 1
  chamber2O[i] == LOW; // Turns off pump/heater/solenoid valves in  Chamber 2
  }

  delay(1000*60*720); // 1000 ms * 60s * 720 min (12 hour delay)
{    
    Adafruit_MAX31855 thermocouple(8,12,13);   
    double e = thermocouple.readFarenheit();

    if( e < 125) {
while(pumpTimer < T1) { // Time Constraint 1
   //Adafruit_MAX31855 thermocouple(chamber1I[0], chamber1I[1], chamber1I[2]); // initialize thermocouple 2 for Micro
   Adafruit_MAX31855 thermocouple(chamber1I[0], chamber1I[1], chamber1I[2]); // initialize thermocouple 2 for Trinket
   Serial.println(thermocouple.readInternal()); // prints data into text
   double c = thermocouple.readFarenheit(); // thermocouple converts data to F
   
   analogWrite(chamber1O[1], HIGH); // solenoid valve is energized to 5V
   delay(50); // delays for 50 ms
   analogWrite(chamber1O[1], 127); // solenoid valve supplied with 3.3V
     
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
}
    }
}
//Stops cycling
  pumpTimer = 0; // reset counter

  for( int i = 0; i < 3; i++) {
  chamber1O[i] == LOW; // Turns off power to pump/heater/solenoid valves in  Chamber 1
  chamber2O[i] == LOW; // Turns off power to pump/heater/solenoid valves in  Chamber 2
  }
  delay(1000*60*720); // 1000 ms * 60s * 720 min (12 hour delay)
}
