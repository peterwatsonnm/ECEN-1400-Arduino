/*
Written by Peter Watson and Arman Sohail as a modification of the following code:
http://www.arduino.cc/en/Tutorial/AnalogInOutSerial

Controls speed and direction of a DC motor with use of a pot and Arduino uno
*/

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 10; // Analog output pin that the motor controller is attatched to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM 

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}

void loop() {
  
  sensorValue = analogRead(analogInPin);
  // map to the range of the analog out: (8 bit)
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  
  //control the direction:  half of the pot's range turns it left, the other half turns it right.
  if (outputValue < (127.5))
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);                      //switches direction of motor
    outputValue = 255 - (outputValue * 2);    //allows values of 0-127.5 to be outputed as values from 0-255
  }
  else  if (outputValue > (127.5))
  {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);                     //switches direction of motor
    outputValue = (outputValue - 127.5)*2;      //allows values of 127.5-255 to be outputted as values from 0-255
  }
  // write outputValue out as PWM to motor controller
  analogWrite(analogOutPin, outputValue);

}
