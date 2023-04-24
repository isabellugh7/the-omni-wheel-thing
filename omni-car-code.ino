#include <Wire.h>
#include <MPU6050.h>

#define speedPinR 3    //  RIGHT PWM pin connect MODEL-X ENA
#define RightDirectPin1  5    //Right Motor direction pin 1 to MODEL-X IN1 
#define RightDirectPin2  4    //Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6    // Left PWM pin connect MODEL-X ENB
#define LeftDirectPin1  7    //Left Motor direction pin 1 to MODEL-X IN3 
#define LeftDirectPin2  2   //Left Motor direction pin 1 to MODEL-X IN4 

int val;
MPU6050 mpu;


void setup() {

  pinMode(RightDirectPin1, OUTPUT); 
  pinMode(RightDirectPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
  pinMode(LeftDirectPin1, OUTPUT);
  pinMode(LeftDirectPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}


void x_axis() {

  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  
  if (normAccel.XAxis > 2) {
    digitalWrite(RightDirectPin1, HIGH);
    digitalWrite(RightDirectPin2, LOW);
  } else if (normAccel.XAxis < -2) {
    digitalWrite(RightDirectPin1, LOW);
    digitalWrite(RightDirectPin2, HIGH);
  } else {
    digitalWrite(RightDirectPin2, LOW);
    digitalWrite(RightDirectPin2, LOW);
  }

  analogWrite(speedPinL,200);
  analogWrite(speedPinR,200);
}

void y_axis() {

  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

  if (normAccel.YAxis > 2) {
    digitalWrite(LeftDirectPin1, LOW);
    digitalWrite(LeftDirectPin2, HIGH);
  } else if (normAccel.YAxis < -2){
    digitalWrite(LeftDirectPin1, HIGH);
    digitalWrite(LeftDirectPin2, LOW);
  } else {
    digitalWrite(LeftDirectPin2, LOW);
    digitalWrite(LeftDirectPin2, LOW);
  }

  analogWrite(speedPinL,200);
  analogWrite(speedPinR,200);
}

void loop() {

  x_axis();
  y_axis();

}
