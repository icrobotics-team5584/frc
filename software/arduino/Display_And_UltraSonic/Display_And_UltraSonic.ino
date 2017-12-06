/***********************************************
* Count down using millis()
*
* Adafruit 7-segment, I2C, LED backpack display
*
* pin A5 -> C (on 7-segment)
* pin A4 -> D (on 7-segment)
*
************************************************/

#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
Adafruit_7segment matrix = Adafruit_7segment();

//unsigned long previousSecondMillis = 0UL;
//long oneSecond = 1000UL; // milliseconds per second

//#define startMinute 10  //  Modify these defines to
//#define startSecond 59 // change the timer interval
//int minutes = startMinute;
//int seconds = startSecond;

//Ultrasonic Pins
#define trigPin 11
#define echoPin 10

//Variable Decleared for RangeFinding
int val=0;
int val1;
int val2;
int val3;
int val4;

void setup()
{
  matrix.begin(0x70);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
      long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  val = distance;
  Serial.print("Val = ");
  Serial.println(val);     // reading the values
  if (val<500){
  val1 = val/1000;
  val2 = (val-(val1*1000))/100;
  val3 = (val-((val1*1000) + (val2*100)))/10;
  val4 = (val-((val1*1000) + (val2*100) + (val3*10)));
  }
   else {
  val1 = 0;
  val2 = 5;
  val3 = 0;
  val4 = 0;
  }

  
  // --------- Run this every second ------------------
 // if (millis() - previousSecondMillis >= oneSecond) {

    matrix.writeDigitNum(0, (val1));
    matrix.writeDigitNum(1, (val2));
    matrix.writeDigitNum(3, (val3));
    matrix.writeDigitNum(4, (val4));
    matrix.writeDisplay();
    delay (50);
    //if (seconds-- == 0) {
     // if (minutes == 0) {
       // minutes = startMinute;
       // delay(1000);
    //  } else {
     //   minutes -= 1;
      //  seconds = 59;
     // }
   // }

  // previousSecondMillis += oneSecond;
 // }
}
