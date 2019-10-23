#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h" 
#include <math.h>

MMA8452Q accel;                   // create instance of the MMA8452 class

void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

}

void loop() {
  if (accel.available()) 
  {  // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    float posX = (accel.getCalculatedX());
    float posY = (accel.getCalculatedY());
    float posZ = (accel.getCalculatedZ());
   
    float thetaX = (57.3 * (atan(posX / sqrt((pow(posY, 2)) + (pow(posZ, 2)))))) + 2.3;     //subtract offset
    float thetaY = (57.3 * (atan(posY / sqrt((pow(posX, 2)) + (pow(posZ, 2)))))) - 0.6;
    float thetaZ = (57.3 * (atan(sqrt((pow(posY, 2)) + (pow(posX, 2))) / posZ))) - 2.2;
     
    Serial.print(thetaX, 3);
    Serial.print("\t");
    Serial.print(thetaY, 3);
    Serial.print("\t");
    Serial.print(thetaZ, 3);
    Serial.println();
  }

}
