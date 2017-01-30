#include <Servo.h>

//PIR Sensor Pins
#define pirPin 3

//Ping Sensor Pins
#define trigPin 5
#define echoPin 4


//7-Segment LED Pins
#define A 7
#define B 8
#define C 9
#define D 10
#define E 11
#define F_SEG 12
#define G 13

//Misc. Definitions
#define aref_voltage 3.3
#define ON HIGH
#define OFF LOW

// Microphone Variables
#define MIC A2
#define LED1 A5

//Temperature Variables
int tempPin = 0;
#define LED2 A6

//Reflective Sensor Variables
int reflectivePin = 1;

//Servo Variables
Servo servoMain;

//PIR Sensor Variables
int pirState = LOW;

void setup() 
{
  //LED Setup
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);

  //Mic Setup
  pinMode(LED1, OUTPUT);

  //Temperature Setup
  analogReference(EXTERNAL);
  pinMode(LED2, OUTPUT);

  //Servo Setup
  servoMain.attach(6); //Connects the Servo to Digital Pin 6

  //Ping Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); 


}

void loop() 
{
  int reflective = Reflective();
  float temp = Temp();
  long ping = Ping();
  int pir = Pir();
  int mic = Mic();

//  Serial.print("Reflective = ");
//  Serial.println(reflective);
//  delay(1000);
//  Serial.print("Temp = ");
//  Serial.println(temp);
//  delay(1000);
//  Serial.print("Ping = ");
//  Serial.println(ping);
//  delay(1000);
//  Serial.print("Pir = ");
//  Serial.println(pir);
//  delay(1000);
//  Serial.print("Mic = ");
//  Serial.println(mic);
//  delay(1000);
  start:
    
  if (reflective > 400)
  {
    if (temp > 25.00 && temp <= 30.00)
    {
      digitalWrite(LED1, OFF);
      if(mic < 100)
      {
        ping:
        
        three();
        servoMain.write(90);
        delay(500);
        ping = Ping();
        
        if (ping > 4 && ping <= 10) 
        {  
          servoMain.write(0);
          
          while(1)
          {
            four();
            pir = Pir();
            reflective = Reflective();

            if(reflective < 400)
            {
              goto shutdwn;
            }

            if(temp > 30.00)
            {
              digitalWrite(LED1, ON);
            }
            
            if (pir == HIGH) 
            {            // check if the input is HIGH
              if (pirState == LOW) 
              {
                // we have just turned on
                Serial.println("Motion detected!");
                pirState = HIGH;
              }
            } 
            else 
            {
              if (pirState == HIGH)
              {
                 // we have just turned off
                 Serial.println("Motion ended!");
                pirState = LOW;
                three();
                delay(250);
                two();
                delay(250);
                one();
                delay(250);
                zero();
                delay(250);
                goto ping;
                
              }
            }  
          }
        }
      }
      else
      {
        servoMain.write(0);
        while(1)
        {
          mic = Mic();
          
          if(mic < 100)
          {
            goto start;
          }
          else
          {
            //two();
            //delay(5000);
          }
        }
      } 
    }
    else
    {

      digitalWrite(LED1, ON);
      
//      while(1)
//      {
//        temp = Temp();
//        if(temp > 25 && temp <= 28)
//        {
//          digitalWrite(LED1, OFF);
//          goto start; 
//        }
//        else
//        {
//          one();
////          servoMain.write(0);
////          delay(250);
////          servoMain.write(90);
////          delay(250);
////          servoMain.write(0);
//          digitalWrite(LED1, ON);
//          digitalWrite(LED2, ON);
//        }
//      }
    }
  }
  else
  {
    servoMain.write(0);
    while(1)
    {
      reflective = Reflective();
       if(reflective > 400)
       {
        goto start;
       }
       else
       {
        shutdwn:
        
        zero();
        digitalWrite(LED1, OFF);
       }
    }
  }
}

int Reflective()
{
  int reflectiveValue = analogRead(reflectivePin);

  return reflectiveValue;
}

float Temp()
{
  int tempReading = analogRead(tempPin);
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 50;
 
  return temperatureC;
}

long Ping()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  return distance;
}

int Pir()
{
  int pirValue = 0;
  pirValue = digitalRead(pirPin);

  return pirValue;
}



int Mic() 
{

  int micReading = analogRead(MIC)*300;

  return micReading;

}

// 0 => ABCDEF
void zero() 
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, OFF);
}

// 1 => BC
void one() 
{
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, OFF);
}

// 2 => ABDEG
void two() 
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, OFF);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, ON);
}

// 3 => ABCDG
void three() 
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, ON);
}

// 4 => BCFG
void four() 
{
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 5 => ACDFG
void five() 
{
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 6 => ACDEFG
void six() 
{
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 7 => ABC
void seven() 
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, OFF);
}

// 8 => ABCDEFG
void eight() 
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 9 => ABCDFG
void nine() 
{
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

