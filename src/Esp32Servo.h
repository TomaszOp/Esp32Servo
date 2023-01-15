#ifndef _Esp32Servo_H__
#define _Esp32Servo_H__

#include <Arduino.h>

#define LEDC_CHANNEL_0  0
#define LEDC_CHANNEL_1  1
#define LEDC_CHANNEL_2  2
#define LEDC_CHANNEL_3  3

#define DEFAULT_CHANNEL  LEDC_CHANNEL_0

#define DEFAULT_uS_LOW 1000        // 1000us
#define DEFAULT_uS_HIGH 2000      // 2000us

// Values for TowerPro SG90 small servos
//#define DEFAULT_uS_LOW 400
//#define DEFAULT_uS_HIGH 2400

#define DEFAULT_TIMER_WIDTH 16
//#define DEFAULT_TIMER_WIDTH_TICKS 65536

#define MIN_PULSE_WIDTH       500     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2500     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define DEFAULT_PULSE_WIDTH_TICKS 4825
#define DEFAULT_PWM_FREQ     50
#define REFRESH_USEC         20000 



class Servo
{
public:
  Servo();
  ~Servo();

  int attach(int pin);                   
  int attach(int pin, int min, int max); 
  int attach(int pin, int min, int max, int channel);
  int attach(int pin, int min, int max, int channel, int pwmReq);
  int attach(int pin, int min, int max, int channel, int pwmReq, int res);
  void detach();
  void write(int value);                 
  void writeMicroseconds(int value);    
  int read();                           
  int readMicroseconds();              
  bool attached();                       
  
  void setTimerWidth(int value);     
  int readTimerWidth();               

  private: 
   int usToTicks(int usec);
   int ticksToUs(int ticks);

   int servoChannel = DEFAULT_CHANNEL;                // channel number for this servo
   int min = DEFAULT_uS_LOW;                          // minimum pulse width for this servo   
   int max = DEFAULT_uS_HIGH;                         // maximum pulse width for this servo 
   int pinNumber = 14;                                 // GPIO pin assigned to this channel
   int timer_width = DEFAULT_TIMER_WIDTH;             // ESP32 allows variable width PWM timers
   int ticks = DEFAULT_PULSE_WIDTH_TICKS;             // current pulse width on this channel
   int timer_width_ticks = pow(2,this->timer_width); //DEFAULT_TIMER_WIDTH_TICKS; // no. of ticks at rollover; varies with width
   bool is_attached;
   int pwm_req = DEFAULT_PWM_FREQ;
   int resolution = DEFAULT_TIMER_WIDTH;
}; 

#endif
