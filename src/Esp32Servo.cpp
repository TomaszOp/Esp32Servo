#include "Arduino.h"

#include "ESP32Servo.h"
#include "esp32-hal-ledc.h"

#define LEDC_CHANNEL_0  0
#define LEDC_CHANNEL_1  1
#define LEDC_CHANNEL_2  2
#define LEDC_CHANNEL_3  3

Servo::Servo()
{
    this->servoChannel = LEDC_CHANNEL_0;

    this->ticks = DEFAULT_PULSE_WIDTH_TICKS;   
    this->timer_width = DEFAULT_TIMER_WIDTH;
    this->pinNumber = -1;   
    this->min = DEFAULT_uS_LOW;
    this->max = DEFAULT_uS_HIGH;
    this->timer_width_ticks = pow(2,this->timer_width);
    this->is_attached = false;
    this->pwm_req = DEFAULT_PWM_FREQ;
}

int Servo::attach(int pin)
{
    return this->attach(pin, DEFAULT_uS_LOW, DEFAULT_uS_HIGH);
}

int Servo::attach(int pin, int min, int max)
{    
    this->pinNumber =  pin;

    this->min = min;     //store this value in uS
    this->max = max;    //store this value in uS

    return this->attach(pin, DEFAULT_uS_LOW, DEFAULT_uS_HIGH, this->servoChannel);       
}
 
int Servo::attach(int pin, int min, int max, int channel) 
{
    this->servoChannel = channel;
    this->pinNumber =  pin;
    this->min = min;     
    this->max = max;    

    return this->attach(pin, DEFAULT_uS_LOW, DEFAULT_uS_HIGH, this->servoChannel, this->pwm_req); 
}

int Servo::attach(int pin, int min, int max, int channel, int pwmReq) 
{
    this->servoChannel = channel;
    this->pinNumber =  pin;
    this->min = min;     
    this->max = max;    
    this->pwm_req = pwmReq;

   return this->attach(pin, min, max, channel, pwmReq, this->timer_width); 
}

int Servo::attach(int pin, int min, int max, int channel, int pwmReq, int res) 
{
    this->servoChannel = channel;
    this->pinNumber =  pin;
    this->min = min;     
    this->max = max;    
    this->pwm_req = pwmReq;
    this->timer_width = res;

    ledcSetup(this->servoChannel, this->pwm_req, this->timer_width); // channel #, 50 Hz, timer width
    ledcAttachPin(this->pinNumber, this->servoChannel);   // GPIO pin assigned to channel 

    this->is_attached = true; 

    return 1;
}


Servo::~Servo() 
{
    detach();
}

void Servo::detach()
{
    if (this->attached())
    {
        ledcDetachPin(this->pinNumber);
        //keep track of detached servos channels so we can reuse them if needed
        this->is_attached = false;
    }
} 

void Servo::write(int value)
{
    if (value < MIN_PULSE_WIDTH)
    {
        if (value < 0)
            value = 0;
        else if (value > 180)
            value = 180;

        value = map(value, 0, 180, this->min, this->max);
    }
    this->writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
    if (this->attached())   // ensure channel is valid
    {
        if (value < this->min)          // ensure pulse width is valid
            value = this->min;
        else if (value > this->max)
            value = this->max;

        value = usToTicks(value);  // convert to ticks
        this->ticks = value;
        // do the actual write
        ledcWrite(this->servoChannel, this->ticks);
    }
}

int Servo::read() // return the value as degrees
{
    return (map(readMicroseconds()+1, this->min, this->max, 0, 180));
}

int Servo::readMicroseconds()
{
    int pulsewidthUsec;
    if (this->attached())
    { 
        pulsewidthUsec = ticksToUs(this->ticks);
    }
    else
    {
        pulsewidthUsec = 0;
    }

    return (pulsewidthUsec);
}
 
bool Servo::attached()
{
    return this->is_attached;
}

void Servo::setTimerWidth(int value)
{
    // only allow values between 16 and 20
    if (value < 16)
        value = 16;
    else if (value > 20)
        value = 20;
      
    int widthDifference = this->timer_width - value;
    if (widthDifference > 0)
    {
        this->ticks << widthDifference;
    }
    else
    {
        this->ticks >> widthDifference;
    }
    
    this->timer_width = value;
    this->timer_width_ticks = pow(2,this->timer_width);
    
    // If this is an attached servo, clean up
    if (this->attached())
    {
        // detach, setup and attach again to reflect new timer width
        ledcDetachPin(this->pinNumber);
        ledcSetup(this->servoChannel, this->pwm_req, this->timer_width);
        ledcAttachPin(this->pinNumber, this->servoChannel);
    }        
}

int Servo::readTimerWidth()
{
    return (this->timer_width);
}

int Servo::usToTicks(int usec)
{
    return (int)((float)usec / ((float)REFRESH_USEC / (float)this->timer_width_ticks));   
}

int Servo::ticksToUs(int ticks)
{
    return (int)((float)ticks * ((float)REFRESH_USEC / (float)this->timer_width_ticks)); 
} 



