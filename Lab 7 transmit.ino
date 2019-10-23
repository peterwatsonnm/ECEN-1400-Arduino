#include <SoftwareSerial.h>
#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h" 
#include <math.h>


MMA8452Q accel;                   // create instance of the MMA8452 class
const byte rxPin = 10;
const byte txPin = 9;
SoftwareSerial serialPin(rxPin, txPin);   //RX TX, set up new serial object

void setup() {
  //set pin modes
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  serialPin.begin(19200);    //set data rate
  Wire.begin();
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
  serialPin.println("Test?");
}

void loop() {
  byte XFlag = 201;
  byte YFlag = 202;
  byte ZFlag = 203;
  int thetaToTransmitX;
  int thetaToTransmitY;
  
  if (accel.available()) 
  {  // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    float posX = (accel.getCalculatedX());
    float posY = (accel.getCalculatedY());
    float posZ = (accel.getCalculatedZ());
   
    float thetaX = (57.3 * (atan(posX / sqrt((pow(posY, 2)) + (pow(posZ, 2))))));     //subtract offset
    float thetaY = (57.3 * (atan(posY / sqrt((pow(posX, 2)) + (pow(posZ, 2))))));
    float thetaZ = (57.3 * (atan(sqrt((pow(posY, 2)) + (pow(posX, 2))) / posZ)));
     
    //Serial.print(thetaX, 3);
    //Serial.print("\t");
    //Serial.print(thetaY, 3);
    //Serial.print("\t");
    //Serial.print(thetaZ, 3);
    //Serial.println();

    int thetaToTransmitX = int(thetaX + 90);    //convert to integer value and add 90 to change range from -90 to 90 to 0 to 180
    int thetaToTransmitY = int(thetaY + 90);
    int thetaToTransmitZ = int(thetaZ + 90);

    Serial.print(thetaToTransmitX);
    Serial.print("\t");
    Serial.print(thetaToTransmitY);
    Serial.print("\t");
    Serial.print(thetaToTransmitZ);
    Serial.println();
    
    //send values preceded by their flag
    serialPin.write(XFlag);
    serialPin.write(thetaToTransmitX);
    serialPin.write(YFlag);
    serialPin.write(thetaToTransmitY);
    serialPin.write(ZFlag);
    //serialPin.write(thetaToTransmitZ);    //only to interface insar's code
    delay(50);
  }
  

}
