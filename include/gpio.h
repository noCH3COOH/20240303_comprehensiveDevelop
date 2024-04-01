#ifndef _LED_H_
#define _LED_H_

// ==================== includes ====================

#include <Arduino.h>
#include "delayNoBlock.h"
#include "ESPAsyncWebServer.h"

#include "log.h"

// ==================== defines ====================

#define LED_connectVCC 

#ifdef LED_connectVCC
    #define LED_ON LOW
    #define LED_OFF HIGH
    #define PWM_CALC(x) (1023 - x)
#else
    #define LED_ON HIGH
    #define LED_OFF LOW
    #define PWM_CALC(x) x
#endif

#define BRIGHTNESS_CTRL_LED_CHANNEL 1
#define BRIGHTNESS_CTRL_LED_PIN 1

// ==================== enum ====================

enum GPIO_t_ErrorCode
{
    GPIO_t_ERROR = 0,
    GPIO_t_OK = 1,
    GPIO_t_HIGH = 2,
    GPIO_t_LOW = 3
};

// ==================== classes ====================

class GPIO_t
{
    private:
        uint8_t pin[10];
        uint8_t pin_count = 0;
        uint8_t pin_mode;

        uint8_t pwm_channel;
        uint32_t pwm_duty;
        
        uint8_t pwm_resolution;
        uint32_t pwm_freq;

        bool pwm_flag;
    
    public:
        GPIO_t();
        GPIO_t(uint8_t pin, uint8_t pin_mode);
        GPIO_t(uint8_t pwm_channel, uint8_t pin, uint32_t freq, uint8_t resolution, uint32_t duty);
        ~GPIO_t();

        enum GPIO_t_ErrorCode add_pin(uint8_t pin);
        enum GPIO_t_ErrorCode delete_pin(uint8_t pin);
        
        void on();
        void off();
        
        void set_pwm_channel(uint8_t pwm_channel);
        void set_pwm_duty(uint32_t duty);
        void set_pwm_resolution(uint8_t resolution);
        void set_pwm_freq(uint32_t freq);

        enum GPIO_t_ErrorCode get_pinState(uint8_t pin);
        
        uint8_t get_pin(uint8_t index);
        uint8_t get_pwm_channel();
        uint32_t get_pwm_duty();
        uint8_t get_pwm_resolution();
        uint32_t get_pwm_freq();
};

// ==================== global variables ====================

extern GPIO_t led;

// ==================== functions ====================

void LED_init();
void LED_root();

void getCallback_readLED(AsyncWebServerRequest *request);
void postCallback_setLED(AsyncWebServerRequest *request);

#endif
