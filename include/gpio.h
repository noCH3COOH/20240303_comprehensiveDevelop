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
    #define PWM_CALC(x) int(1023 - x)
#else
    #define LED_ON HIGH
    #define LED_OFF LOW
    #define PWM_CALC(x) int(x)
#endif

#define BRIGHTNESS_CTRL_LED_CHANNEL 1
#define BRIGHTNESS_CTRL_LED_PIN 1

// ==================== enum ====================

enum GPIO_t_ErrorCode
{
    GPIO_t_ERROR = 0,
    GPIO_t_OK = 1
};

template <typename T>
struct GPIO_t_retval {
    T data;
    GPIO_t_ErrorCode err;
};

// ==================== classes ====================

class GPIO_t
{
    private:
        uint8_t pin[10];
        uint8_t pin_count = 0;
        uint8_t pin_mode;

        uint8_t pwm_channel;
        uint8_t pwm_duty;
        
        uint8_t pwm_resolution;
        uint32_t pwm_freq;

        bool pwm_flag;
        bool adc_flag;
        const uint8_t adc_bit = 12;
    
    public:
        GPIO_t();
        GPIO_t(uint8_t pin);
        ~GPIO_t();

        GPIO_t_retval<bool> on();
        GPIO_t_retval<bool> off();
        
        GPIO_t_retval<bool> add_pin(uint8_t pin);
        GPIO_t_retval<bool> delete_pin(uint8_t pin);
        
        GPIO_t_retval<bool> set_mode(uint8_t pin_mode);
        GPIO_t_retval<bool> set_mode_pwm(uint8_t pwm_channel, uint32_t freq, uint8_t resolution, uint8_t duty);
        GPIO_t_retval<bool> set_mode_adc();
        
        GPIO_t_retval<bool> set_pwm_channel(uint8_t pwm_channel);
        GPIO_t_retval<bool> set_pwm_resolution(uint8_t resolution);
        GPIO_t_retval<bool> set_pwm_duty(uint8_t duty);
        GPIO_t_retval<bool> set_pwm_freq(uint32_t freq);

        GPIO_t_retval<int8_t> get_pinState(uint8_t pin);
        GPIO_t_retval<uint8_t> get_pin(uint8_t index);
        GPIO_t_retval<uint8_t> get_pwm_channel();
        GPIO_t_retval<uint8_t> get_pwm_resolution();
        GPIO_t_retval<uint8_t> get_pwm_duty();
        GPIO_t_retval<uint32_t> get_pwm_freq();
        GPIO_t_retval<float> get_adc_value(uint8_t pin);
};

// ==================== global variables ====================

extern GPIO_t led;

// ==================== functions ====================

void LED_init();
void LED_root();

void getCallback_readLED(AsyncWebServerRequest *request);
void postCallback_setLED(AsyncWebServerRequest *request);

#endif
