#include <Servo.h>

Servo servoMain;

void setup()
{
    servoMain.attach(6);
}

void loop()
{  
   servoMain.write(180);
   delay(1000);
   servoMain.write(0);
   delay(1000);
}
