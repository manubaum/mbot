#include <Arduino.h>
#include <MeMCore.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "math.h"

/*

  Hardware:
  Port1         Thermometer
  Port2         Linesensor
  Port3         Ultrasonic
  Port4         4 digit 7-segment display
*/

//Port 3
MeUltrasonicSensor ultrasonic(PORT_3);

// Port 4
Me7SegmentDisplay display(PORT_4);

// built in LED
MeRGBLed rgbled(7, 2);

// Makeblock Motors
MeDCMotor motor_left(9);
MeDCMotor motor_right(10);


void _delay(float seconds) {
    long endTime = millis() + seconds * 1000;
    while (millis() < endTime) _loop();
}

void setup() {

    // RJ25 adapter
    Serial.begin(9600);


    display.init();
    display.set(BRIGHTNESS_2);

    rgbled.show();

}


long CRITICAL_DISTANCE = 50;


void _loop() {
}

void loop() {
    _loop();

    long leftOrRight = ((uint16_t)ultrasonic.distanceCm()%2)==1?3:4;

    //start scanning for good direction
    move(leftOrRight, 50 / 100.0 * 255);
    rgbled.setColor(0,255,0,0);
    rgbled.show();

    while(true){
        uint16_t distance = ultrasonic.distanceCm();
        display.display(distance);

        if(distance !=400 && distance > 150){
            break;
        }
    }

    _delay(0.150 );

    // go straight into that direction until obstacle found
    move(1, 50 / 100.0 * 255);
    rgbled.setColor(0,0,255,0);
    rgbled.show();

    while(true){
        uint16_t distance = ultrasonic.distanceCm();
        display.display(distance);

        if(distance ==400)
        {
            break;
        }

        if(distance < CRITICAL_DISTANCE){
            break;
        }
    }

    move(0, 0);
    /*
    uint16_t bestAngle = 0;
    uint16_t highestDistance = 500;

    for(int degree = 0; degree<360; degree++)
    {
       uint16_t distance =ultrasonic.distanceCm();
      if(distance < highestDistance)
      {
          bestAngle=degree;
          highestDistance=distance;

      }
      display.display(distance);
      _delay(0.0032);
    }*/


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

