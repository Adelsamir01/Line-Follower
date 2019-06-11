#include <ADXL345.h>
#include <Wire.h>
#include<Servo.h>
int pos2 = 0;
Servo servo1;
Servo servo2;
int k = 0;
int laser = 60;
int laserreading;
int triggerpin_l = 25;
int triggerpin_m = 2;
int triggerpin_r = 23;
int echopin_l = 22;
int echopin_m = 3;
int echopin_r = 24;
int distance_l;
int distance_m;
int pos1 = 0;
int distance_r;
int s2_r = 11 ;
int s3_r = 10 ;
int outpin_r = 12;
int s2_l = 27;
int s3_l = 26 ;
int outpin_l = 28 ;
int red_r;
int green_r;
int blue_r;
int red_l;
int green_l;
int blue_l;
int red;
int blue;
int green;
int triggerpin = 9;
int distance;
float echotime;
float soundspeed = 0.034024;
int l1 = A0;
int l2 = A1;
int m = A2;
int r1 = A3;
int r2 = A4;
int left1;
int left2;
int middle;
int right1;
int right2;
int in1 = 5;
int in2 = 4;
int in3 = 7;
int in4 = 6;
int ena = 9;
int enb = 8;
int H;
ADXL345 adxl;
void setup() {
  servo1.attach(57);
  servo2.attach(58);
  Serial.begin(9600);
  adxl.powerOn();
  pinMode(s2_r, OUTPUT);
  pinMode(s3_r, OUTPUT);
  pinMode(outpin_r, INPUT);
  pinMode(s2_l, OUTPUT);
  pinMode(s3_l, OUTPUT);
  pinMode(outpin_l, INPUT);
  pinMode(echopin_m, INPUT);
  pinMode(triggerpin_m, OUTPUT);
  pinMode(echopin_l, INPUT);
  pinMode(triggerpin_l, OUTPUT);
  pinMode(echopin_r, INPUT);
  pinMode(triggerpin_r, OUTPUT);
  pinMode(laser, INPUT);
  pinMode(r1 , INPUT);
  pinMode(r2 , INPUT);
  pinMode(m , INPUT);
  pinMode(l1 , INPUT);
  pinMode(l2 , INPUT);
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  pinMode(in3 , OUTPUT);
  pinMode(in4 , OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  adxl.setActivityThreshold(75);
  adxl.setInactivityThreshold(75);
  adxl.setTimeInactivity(10);
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
  adxl.setTapThreshold(50);
  adxl.setTapDuration(15);
  adxl.setDoubleTapLatency(80);
  adxl.setDoubleTapWindow(200);
  adxl.setFreeFallThreshold(7);
  adxl.setFreeFallDuration(45);
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 80);
  analogWrite(enb, 80);
}
void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 60);
  analogWrite(enb, 60);
}
void forward1() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 45);
  analogWrite(enb, 45);
}
void back() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 60);
  analogWrite(enb, 60);
}
void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 80);
  analogWrite(enb, 80);
}
void rotate() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 80);
  analogWrite(enb, 80);
}
void pause() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void forward_fast() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 110);
  analogWrite(enb, 110);
}
float ultra(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  float Time = pulseIn(echo, HIGH);
  Time = Time / 2;
  int Distance = Time * soundspeed;
  return Distance;
}


void rgb(int s2, int s3, int outpin) {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(outpin, LOW);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  green = pulseIn(outpin, LOW);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blue = pulseIn(outpin, LOW);
}

void loop() {
  int x, y, z;
  adxl.readAccel(&x, &y, &z);
  byte interrupts = adxl.getInterruptSource();
//  Serial.println(H);
  while (x > 45) {
    adxl.readAccel(&x, &y, &z);
    forward_fast();

  }
  distance_m = ultra(triggerpin_m, echopin_m);

  rgb(s2_r, s3_r, outpin_r);
  red_r = red;
  green_r = green;
  blue_r = blue;
  rgb(s2_l, s3_l, outpin_l);
  red_l = red;
  green_l = green;
  blue_l = blue;
  Serial.print(red_r);
   Serial.print(",");
   Serial.print(green_r);
    Serial.print(",");
    Serial.println(blue_r);
  right1 = digitalRead(r1 );
  right2 = digitalRead(r2);
  middle = digitalRead(m);
  left1 = digitalRead(l1);
  left2 = digitalRead(l2);
  if  (green_r < blue_r && green_r < red_r && green_r > 70  && green_r < 200) {
    delay(10);
    if (green_l < blue_l && green_l < red_l && green_l > 70  && green_l < 200)
    {
      right();
      Serial.println("return");
      delay(4000);
    }
    else
    { Serial.println("right");
      right();
      delay(1250);
      forward();
      delay(600);
    }
  }
  else if (green_l < blue_l && green_l < red_l && green_l > 70  && green_l < 200)
  {
    delay(10);
    if  (green_r < blue_r && green_r < red_r && green_r > 70  && green_r < 200)
    {
      right();
      Serial.println("return");
      delay(4000);
    }
    else
    { Serial.println("left");
      left();
      delay(1250);
      forward();
      delay(600);
    }
  }

  else if (distance_m < 5) {

    back();
    delay(500);
    right();
    delay(1200);
    forward();
    delay(750);
    left();
    delay(900);
    forward();
    delay(1000);
    left();
    delay(800);
    forward();
    delay(850);
  }



  /*  Serial.print(green_l);
    Serial.print(" , ");
    Serial.print(blue_l);
    Serial.print(" , ");
    Serial.println(red_l);*/
  H = right2 + 2 * right1 + 4 * middle + 8 * left2 + 16 * left1;

  if ( H == 17 or H == 27) {
    forward();
  }
  else if (H == 19  or H == 29 or H == 30 or H == 32) {
    right();
  }
  else if ( H == 15 or H == 23 or H == 25 or H == 33) {
    left();

  }
  else if (H == 7 or H == 35 or H == 3 or H == 11 or H == 1 or H == 21) {
    left();
    delay(900);

  }
  else if (H == 24 or H == 28 or H == 40 or H == 26 or H == 16 or H == 5 or H == 26) {
    right();
    delay(900);
  }
  else if (H == 31 or H == 35  ) {
    forward1();
  }
  else if ( H == 41 or H == 0) {
    forward();
    delay(200);
  }

  while (green_r < 1 && green_r > 5000 && red_r < 7000 && red_r > 5000 && blue_r > 2000 && blue_r < 8000) {
    distance_m = ultra(triggerpin_m, echopin_m);
    distance_l = ultra(triggerpin_l, echopin_l);
    distance_r = ultra(triggerpin_r, echopin_r);

    if (distance_l > 25 && distance_m > 25 && distance_r > 25) {
      forward();
    }
    else if (distance_r < 15 && distance_r > 25) {
      right();
    }

    else if (distance_l < 15 && distance_l > 25) {
      left();
    }
    else if (distance_m < 15 && distance_m > 25) {
      forward();
    }
    else if (distance_r < 10 && distance_l < 10 && distance_m < 10) {

      if (k = 0) {
        k = 1;
        right();
        delay(1000);
        forward();
        delay(500);
        left();
        delay(1000);
      }
      else if (k = 1)
      { k = 0;
        left();
        delay(1000);
        forward();
        delay(500);
        right();
        delay(1000);

      }
    }
    else if (distance_m < (distance_l - 3) && distance_m < (distance_r - 3) && distance_m < 20  ) {
      for (pos1 = 0; pos1 <= 180; pos2 += 1) {
        servo1.write(pos1);
        delay(15);
      }
      // gripper code
      for (pos2 = 0; pos2 <= 180; pos2 += 1) {
        servo2.write(pos2);
        delay(15);
      }

      for (pos1 = 180; pos1 >= 0; pos1 -= 1) {
        servo1.write(pos1);
        delay(15);
      }
      for (pos2 = 180; pos2 >= 0; pos2 -= 1) {
        // in steps of  degree
        servo2.write(pos2);
        delay(15);
      }
      delay(1000);
      laserreading = digitalRead(laser);
      while (laserreading = 1)
      {
        laserreading = digitalRead(laser);
        rotate();
      }

      if (laserreading = 0) {
        right();
        delay(1000);
        forward();
        delay(6000);

      }
      for (pos1 = 0; pos1 <= 180; pos2 += 1) {
        // in steps of  degree
        servo1.write(pos1);
        delay(15);
      }

      for (pos1 = 180; pos1 >= 0; pos1 -= 1) {
        // in steps of  degree
        servo1.write(pos1);
        delay(15);
      }
    }
    else if (distance_r < 15 && distance_l > 17 && distance_m > 17) {
      back();
      delay(500);
      right();
      delay(100);
    }
    else if (distance_l < 15 && distance_r > 17 && distance_m > 17) {
      back();
      delay(500);
      left();
      delay(100);
    }
  }
}
