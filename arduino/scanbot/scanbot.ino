// generated by mBlock5 for mBot
// codes make you happy

#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "math.h"

/*

  Hardware:
  Port1       Ultrasonic (rotating)
  Port2       RJ25 output
      Slot 1: Analog Servo
      Slot 2: -
  Port3       Ultrasonic (facing down)
  Port4       4 digit 7-segment display
*/

//Port 1
MeUltrasonicSensor rotatingUltrasonic(PORT_1);

//Port 2
Servo servo;
MePort port_2(2);

//Port 3
MeUltrasonicSensor lowerUltrasonic(PORT_3);

// Port 4
Me7SegmentDisplay display(PORT_4);

boolean stateLED = false; // true -> on, false -> off
boolean stateDisplay = false; //true -> on, false -> off

char string_data[] = "Hallo Maro";
int move_times = sizeof(string_data)*6;

uint8_t Bitmap_Heart[16]=
{
 0x00,0x38,0x44,0x42,0x21,0x21,0x42,0x44,0x38,0x44,0x42,0x21,0x21,0x42,0x44,0x38,
};


void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime) _loop();
}

void setup() {

  // RJ25 adapter
  Serial.begin(9600);

  servo.attach(port_2.pin1());
  servo.write(90);

  delay(20);

}



void _loop() {
}

void loop() {
  _loop();




  



  delay(10);//ms
}
