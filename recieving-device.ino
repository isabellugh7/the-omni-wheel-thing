 //nrf2401 receiver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050.h>

#define speedPinR 3    //  RIGHT PWM pin connect MODEL-X ENA
#define RightDirectPin1  5    //Right Motor direction pin 1 to MODEL-X IN1 
#define RightDirectPin2  4    //Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6    // Left PWM pin connect MODEL-X ENB
#define LeftDirectPin1  7    //Left Motor direction pin 1 to MODEL-X IN3 
#define LeftDirectPin2  2   //Left Motor direction pin 1 to MODEL-X IN4

RF24 nrf(9, 8);  // CE, CSN
const byte linkAddress[6] = "link1";  //address through which two modules communicate.
const byte greenLED = 10;
float data[3];
/////////////////////////////////////////////////////////////////////
void setup()
{ 
  pinMode(RightDirectPin1, OUTPUT); 
  pinMode(RightDirectPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
  pinMode(LeftDirectPin1, OUTPUT);
  pinMode(LeftDirectPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
  
  Serial.begin(9600); 
  Serial.println("Starting");
  pinMode(greenLED, OUTPUT);
 
  nrf.begin();    
  nrf.openReadingPipe(0, linkAddress);  //set the address 
  nrf.startListening();   //Set nrf as receiver
}
///////////////////////////////////////////////////
void loop()
{
   digitalWrite(greenLED, HIGH);
   delay(50);
   digitalWrite(greenLED, LOW);
   delay(50);
   
   if (nrf.available())  //Read the data if available in buffer
     {
      nrf.read(&data, sizeof(data));
     Serial.print(data[0]); Serial.print("hPa  ");
     Serial.print(data[1]); 
     Serial.write(0xC2);  //send degree symbol
     Serial.write(0xB0);  //send degree symbol
     Serial.print("C   ");  
     Serial.print(data[2]); Serial.println("m");  
     }  
}
//////////////////////////////////////////////