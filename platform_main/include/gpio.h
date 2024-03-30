#ifndef _LED_H_
#define _LED_H_

// ==================== includes ====================

#include <Arduino.h>

// ==================== defines ====================

#define LED_connectVCC 

#ifdef LED_connectVCC
    #define LED_ON LOW
    #define LED_OFF HIGH
#else
    #define LED_ON HIGH
    #define LED_OFF LOW
#endif

// ==================== functions ====================

void LED_init();
void LED_root();

// ==================== GPIO_t ====================

class GPIO_t
{
    private:
        uint8_t pin;
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
        
        void on();
        void off();
        
        void set_pin(uint8_t pin);
        void set_pwm_channel(uint8_t pwm_channel);
        void set_pwm_duty(uint32_t duty);
        void set_pwm_resolution(uint8_t resolution);
        void set_pwm_freq(uint32_t freq);

        bool get_pinState();
        
        uint8_t get_pin();
        uint8_t get_pwm_channel();
        uint8_t get_pwm_duty();
        uint8_t get_pwm_resolution();
        uint32_t get_pwm_freq();
};

#endif
