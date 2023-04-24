//nrf2401 transmitter:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050.h>

RF24 nrf(9, 8);  // CE, CSN
const byte linkAddress[6] = "link1";

float x_axis;
float y_axis;
float data[3];
char charVal[17];



MPU6050 mpu;

void setup()
{
  Serial.begin(9600);
  nrf.begin();   
  nrf.openWritingPipe(linkAddress);  //set the address 
  //nrf.setPALevel(RF24_PA_LOW);   //keep tx level low to stop psu noise, can remove this but then put in decoupling caps
  // Options are: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,  RF24_PA_HIGH=0dBm.
  nrf.setPALevel(RF24_PA_HIGH); 
  nrf.stopListening();  //act as a transmitter

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{  
 Vector rawAccel = mpu.readRawAccel();
 Vector normAccel = mpu.readNormalizeAccel();

 x_axis = normAccel.XAxis;
 y_axis = normAccel.YAxis;

  
 data[0] = x_axis;
 data[1] = y_axis;
 
 //----- display on local monitor: ------------
 Serial.print(data[0]);
 Serial.print(data[1]); 

  nrf.write(data, sizeof(data)); //spit out the data array
  
  delay(300);
}
