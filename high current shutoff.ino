/*
Get_current_mA function written by Poorn Mehta
Current overload relay shutoff written by Peter Watson
*/

// Constants
#define No_of_Samples             (uint32_t)250
#define Loop_Delay_ms             (uint8_t)1



const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 10;
const int vInPin = A1;

uint32_t Avg_Current, Sample, Avg_Max_Current, Sample_Above_Avg, Sensor_Offset_mA, Over_Current_Wait_Counter;
uint32_t Array_Currents[No_of_Samples];
int Motor_Current_mA;

uint32_t Get_Current_mA(void)
{
  Avg_Current = 0;
  
  for(Sample = 0; Sample < No_of_Samples; Sample++)
  {
       
  
    // Calculate Motor_Current_mA here

      int ADC_voltage = analogRead(vInPin);
   
   float mVolt = (ADC_voltage) * ((uint32_t)5000 / (uint32_t)1023);
   float delta_mVolt;
   if (mVolt >= 2500)
   {
    delta_mVolt = mVolt - 2500;
   }
   else
   {
    delta_mVolt = 2500 - mVolt;
   }
   Motor_Current_mA = (delta_mVolt) * ((uint32_t)1000 /(uint32_t)400);

    
    Array_Currents[Sample] = Motor_Current_mA;
    Avg_Current += Motor_Current_mA;
    delay(Loop_Delay_ms);
  }
   
  Avg_Current /= No_of_Samples;

  Avg_Max_Current = 0;
  
  Sample_Above_Avg = 0;
  
  for(Sample = 0; Sample < No_of_Samples; Sample ++)
  {
    if(Array_Currents[Sample] > Avg_Current)
    {
      Avg_Max_Current += Array_Currents[Sample];
      Sample_Above_Avg += 1;
    }
  }

  return (Avg_Max_Current / Sample_Above_Avg);
}

void setup() 
{
  // Setup pins here
  
  Serial.begin(9600);

  Serial.println("KEEP THE MOTOR OFF");

  Over_Current_Wait_Counter = 0;

  Sensor_Offset_mA = Get_Current_mA();

  Serial.println("TURN ON THE MOTOR");
  //set up motor controller h gate pins
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  pinMode(4, OUTPUT);       //relay control: the relay is default closed, this opens it

}

void loop()
{
  
  Motor_Current_mA = Get_Current_mA();
  Motor_Current_mA -= Sensor_Offset_mA;
  
  if(Motor_Current_mA < 0)
  {
    Motor_Current_mA = 0;
  }
   

   Serial.println(Motor_Current_mA);
   // read the analog in value from pot
  float sensorValue = analogRead(analogInPin);
  
  // map it to the range of the analog out:
  float outputValue = map(sensorValue, 0, 1023, 0, 255);
  
  //send pwm to the motor controller
  analogWrite(analogOutPin, outputValue);
 
  int currentMax_mA = 100;
  if (Motor_Current_mA >= currentMax_mA)
    {
        digitalWrite(4, HIGH);       //opens relay and opens motor circuit
        delay(5000);
        digitalWrite(4, LOW);
    }
  
}
