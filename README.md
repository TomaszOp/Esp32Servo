# Esp32Servo
Esp32 arduino library servo 180 <br>
  <br>
  use <br>
  <br>
  Servo servo; <br>
  <br>
  servo.attach(int pin);   <br>                 
  servo.attach(int pin, int min, int max);  <br>
  servo.attach(int pin, int min, int max, int channel); <br>
  servo.attach(int pin, int min, int max, int channel, int pwmReq); <br>
  servo.attach(int pin, int min, int max, int channel, int pwmReq, int res); <br>
  <br>
  servo.write(int value);   // 0 - 180 <br>         
  servo.writeMicroseconds(int value);   <br>
