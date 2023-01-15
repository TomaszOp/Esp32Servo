# Esp32Servo
Esp32 arduino library servo 180

use
  
  Servo servo;
  
  servo.attach(int pin);                   
  servo.attach(int pin, int min, int max); 
  servo.attach(int pin, int min, int max, int channel);
  servo.attach(int pin, int min, int max, int channel, int pwmReq);
  servo.attach(int pin, int min, int max, int channel, int pwmReq, int res);

  servo.write(int value);                 
  servo.writeMicroseconds(int value);  
