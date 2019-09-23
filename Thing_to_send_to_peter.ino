/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 10; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  if (outputValue < (127.5))
  {
    //outputValue = map(outputValue, 0, 255, 0, 127.5);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);      //switches direction of motor
    outputValue = 255 - (outputValue * 2);
  }
  else  if (outputValue > (127.5))
  {
    //outputValue = map(outputValue, 0, 255, 127.5, 255);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);      //switches direction of motor
    outputValue = (outputValue - 127.5)*2;
  }
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);
  Serial.println(outputValue);

}
