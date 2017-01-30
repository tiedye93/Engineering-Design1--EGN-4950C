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

//Temperature Variables
int tempPin = 0;        
int tempReading;        
float maxTemp = 23.00;

//Reflective Sensor Variables
int reflectivePin = 1;

//Servo Variables
Servo servoMain;

//PIR Sensor Variables
int pirState = LOW;
int pirValue = 0;

// Microphone Variables
#define MIC A2
int micReading = 0;


void setup() {
  //LED Setup
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);

  //Temperature Setup
  analogReference(EXTERNAL);

  //Servo Setup
  servoMain.attach(6); //Connects the Servo to Digital Pin 6

  //Ping Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); 

}

void loop() 
{

  //------------------------Reflective Sensor Readings------------------------------
  int reflectiveValue = analogRead(reflectivePin);
  Serial.println(reflectiveValue);

  //-------------------------Temp Readings-----------------------------
  tempReading = analogRead(tempPin);
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0;
  float temperatureC = (voltage - 0.5) * 50;

  //-------------------------Ping Readings------------------------------
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  //-------------------------PIR Readings-----------------------------
  pirValue = digitalRead(pirPin);  // read input value
  
  
    //*********************PIR Testing*********************
  if (pirValue == HIGH) 
  {            // check if the input is HIGH
    eight();
    if (pirState == LOW) 
    {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 

  else 
  {
    nine();
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  delay(1000);

 
  //*********************Reflective Testing*********************
//  if( reflectiveValue >= 500)
//  {
//    six();
//    delay(1000);
//  }
//  else
//  {
//    seven();
//    delay(1000);
//  }  
   
  //*********************Ping Testing*********************
  if (distance > 4 && distance <= 10) 
  {  // This is where the LED On/Off happens
    four();
    delay(1000);
  }
  else 
  {
    five();
    delay(1000);
  }
  if (distance >= 200 || distance <= 0)
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(1000);

  //*********************Temp & LED Testing*********************
//  if(temperatureC > maxTemp)
//  {
//    one();
//    delay(1000);
//    two();
//    delay(1000);
//    three();
//    delay(1000);
//
//    if (servoMain.read() == 180)
//    {
//      
//    }
//    else
//    {
//      servoMain.write(180);
//    }
//  }
//  else
//  {
//    zero();
//    servoMain.write(0);
//    delay(250);
//    servoMain.write(90);
//    delay(250);
//    servoMain.write(0);
//    
//  }
//
//  delay(1000);


//  servoMain.write(0);
//  delay(1000);
//  servoMain.write(90);
//  delay(1000);
//  servoMain.write(0);

}


void Mic() 
{

 micReading = analogRead(MIC)*10;
 Serial.println(micReading);

 if (micReading>1)  
 {
    zero();
 } 
 
 if (micReading>300)  
 {
    one();
 } 

 if (micReading>800)  
 {
    two();
 } 

 if (micReading>950)  
 {
    three(); 
 } 

}



// 0 => ABCDEF
void zero() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, OFF);
}

// 1 => BC
void one() {
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, OFF);
}

// 2 => ABDEG
void two() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, OFF);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, ON);
}

// 3 => ABCDG
void three() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, ON);
}

// 4 => BCFG
void four() {
  digitalWrite(A, OFF);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 5 => ACDFG
void five() {
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 6 => ACDEFG
void six() {
  digitalWrite(A, ON);
  digitalWrite(B, OFF);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 7 => ABC
void seven() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, OFF);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, OFF);
  digitalWrite(G, OFF);
}

// 8 => ABCDEFG
void eight() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, ON);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}

// 9 => ABCDFG
void nine() {
  digitalWrite(A, ON);
  digitalWrite(B, ON);
  digitalWrite(C, ON);
  digitalWrite(D, ON);
  digitalWrite(E, OFF);
  digitalWrite(F_SEG, ON);
  digitalWrite(G, ON);
}
