#include "ESP32Servo.h"

Servo servo1;

int minUs = 500;
int maxUs = 2400;

int servo1Pin = 14;

int pos = 0;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Init servo");

  servo1.attach(servo1Pin, minUs, maxUs);
}

void loop() 
{
  Serial.print("Start Control");

    servo1.write(0);              
    delay(200); 

    servo1.write(180);              
    delay(200); 


    for (pos = 0; pos <= 180; pos += 1) 
    { 
      Serial.println("Position");
      Serial.println(pos);

      servo1.write(pos);              
      delay(20);                     
    }
}
