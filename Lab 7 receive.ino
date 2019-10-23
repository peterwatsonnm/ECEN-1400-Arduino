
//this goes on the recieving arduino, which runs the servos
#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;
const byte rxPin = 10;
const byte txPin = 11;
SoftwareSerial serialPin(rxPin, txPin);   //RX TX, set up new serial object

void setup() {
  myservo.attach(10);  // bottom servo
  myservo1.attach(11);  //top servo
  //set pin modes
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  serialPin.begin(19200);    //set data rate
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  
  serialPin.println("Test?");
}

void loop() {
  int bytesExpected = 4;      //expects 2 flags and 2 angles
  byte XFlag = 201;
  byte YFlag = 202;
  int XRecieved;
  int YRecieved;
  int posTop;
  int posBottom;
 
  while(serialPin.available() < bytesExpected); //wait until 4 bytes are qued up
    for (int i = 0; i < 2; i++)
    {
      int ReadCode = serialPin.read();
      if(ReadCode == XFlag)
      {
        int XRecieved = serialPin.read();   //if the transmitting arduino flags that it is about to send a theta value, store next data line in the theta value 
      }
      else if(ReadCode == YFlag)
      {
        int YRecieved = serialPin.read();
      }
      else
      {
        Serial.println("ReadCode did not equal PhiFlag or ThetaFlag"); 
      }
    
    }
    
    Serial.println(XRecieved);
    Serial.println(YRecieved);
    if (posTop > XRecieved)
    {
      posTop--;
    }
    if (posTop < XRecieved)
    {
      postop++;
    }
    if (posBottom > YRecieved)
    {
      
    }
    myservo.write(posTop);   //turn bottom servo with theta recieved
    myservo1.write(posBottom);  //turn top servo with phi recieved
    delay(15);
}
