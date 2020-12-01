// generated by mBlock5 for mBot
// codes make you happy

#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "math.h"

/*

  Hardware:
  Port1         Ultrasonic (rotating)
  Port2         RJ25 output
      Slot 1:   Analog Servo
      Slot 2:   -
  Port3         Ultrasonic (facing down)
  Port4         4 digit 7-segment display
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


MeRGBLed rgbled(7, 2);

MeDCMotor motor_left(9);
MeDCMotor motor_right(10);




uint16_t distanceToAobstacle[180];

//volatile byte state = LOW;

volatile uint16_t angle = 0;
volatile uint16_t rotation_direction = 1; // is 1 or -1
volatile uint16_t rotation_speed = 1; // is 1 or -1


void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime) _loop();
}

void setup() {

  // RJ25 adapter
  Serial.begin(9600);

  servo.attach(port_2.pin1());
  //servo.write(120);

  //delay(1000);

  //servo.write(30);

  //delay(2000);

  display.init();
  display.set(BRIGHTNESS_2);
  //splay.display((uint8_t)1, (uint8_t)1);

  rgbled.setColor(0,255,255,255);
  rgbled.show();

  //onboard button
  //pinMode(A7, INPUT);

    // timer set for interrupt
  TIMSK2 = (TIMSK2 & B11111110) | 0x01;
  TCCR2B = (TCCR2B & B11111000) | 0x07;
}



void _loop() {
}

void loop() {
  _loop();


//for (uint16_t angle = 0; angle < 180; angle++){
   //display.display((uint16_t)angle);
   //distanceToAobstacle[angle] = rotatingUltrasonic.distanceCm();
   display.display(rotatingUltrasonic.distanceCm());
   servo.write(angle);
   delay(10);



}



ISR(TIMER2_OVF_vect){

    angle += (rotation_direction * rotation_speed);

    if(angle>=180){
      rotation_direction = -1;  
    }
    else if(angle <= 0)
    {
      rotation_direction = 1;  
    }

 
}

void move(int direction, int speed) {
  int leftSpeed = 0;
  int rightSpeed = 0;
  if(direction == 1) {
    leftSpeed = speed;
    rightSpeed = speed;
  } else if(direction == 2) {
    leftSpeed = -speed;
    rightSpeed = -speed;
  } else if(direction == 3) {
    leftSpeed = -speed;
    rightSpeed = speed;
  } else if(direction == 4) {
    leftSpeed = speed;
    rightSpeed = -speed;
  }
  motor_left.run((9) == M1 ? -(leftSpeed) : (leftSpeed));
  motor_right.run((10) == M1 ? -(rightSpeed) : (rightSpeed));
}
