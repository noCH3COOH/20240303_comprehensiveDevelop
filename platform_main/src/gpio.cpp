#include "gpio.h"

// ==================== global variables ====================

GPIO_t led(BRIGHTNESS_CTRL_LED_CHANNEL, BRIGHTNESS_CTRL_LED_PIN, 5000, 10, 50);

int loop_duty = 0;
bool loop_direation = true;

// ==================== functions ====================

/**
 * @brief 初始化 LED
*/
void LED_init()
{
    led.on();
}

/**
 * @brief LED 主循环
*/
void LED_root()
{
    delayNoBlock_ms(100);
    
    if(loop_direation)
    {
        loop_duty += 50;
    }
    else
    {
        loop_duty -= 50;
    }

    if(loop_duty >= 1024)
    {
        loop_direation = false;
        loop_duty = 1024;
    }
    else if(loop_duty <= 0)
    {
        loop_direation = true;
        loop_duty = 0;
    }

    led.set_pwm_duty(loop_duty);
}

/**
 * @brief 读取 LED PWM数值
*/
void getCallback_readLED(AsyncWebServerRequest *request)
{
    const String str_request = String(std::to_string(PWM_CALC(led.get_pwm_duty()) / 10.23).c_str()) + "%";
    request->send(200, "text/plain", str_request);
}

/**
 * @brief 设置 LED PWM数值
 * @param request 请求
*/
void postCallback_setLED(AsyncWebServerRequest *request)
{
    String pwm = (request->arg("LED_pwm")).c_str();
    int LED_duty;
    std::sscanf(pwm.c_str(), "%d", &LED_duty);

    for(int i=0; i<8; i++)
    {
        led.set_pwm_duty(PWM_CALC(LED_duty * 10.23));
        delayNoBlock_ms(15);
    }
    delayNoBlock_ms(500);

    log_now("[INFO] 设置LED PWM数值为: " + pwm + "% (" + std::to_string(PWM_CALC(LED_duty * 10.23)).c_str() + ')');
    request->send(200, "text/plain", "OK");
}


// ==================== GPIO_t ====================

/**
 * @brief GPIO 构造函数
*/
GPIO_t::GPIO_t()
{
    this->pin = 0;
    this->pin_mode = 0;

    this->pwm_channel = 0;
    this->pwm_duty = 0;
    this->pwm_resolution = 0;
    this->pwm_freq = 0;

    this->pwm_flag = false;
}

/**
 * @brief GPIO 构造函数
 * @param pin 引脚
 * @param pin_mode 引脚模式 INPUT OUTPUT PULLUP INPUT_PULLUP PULLDOWN INPUT_PULLDOWN OPEN_DRAIN OUTPUT_OPEN_DRAIN ANALOG
*/
GPIO_t::GPIO_t(uint8_t pin, uint8_t pin_mode)
{
    this->pin = pin;
    this->pin_mode = OUTPUT;

    this->pwm_channel = 0;
    this->pwm_duty = 0;
    this->pwm_resolution = 0;
    this->pwm_freq = 0;

    this->pwm_flag = false;
}

GPIO_t::GPIO_t(uint8_t pwm_channel, uint8_t pin, uint32_t freq, uint8_t resolution, uint32_t duty)
{
    this->pin = pin;
    this->pin_mode = OUTPUT;


    this->pwm_channel = pwm_channel;
    this->pwm_freq = freq;
    this->pwm_resolution = resolution;
    this->pwm_duty = duty;

    this->pwm_flag = true;
}

/**
 * @brief GPIO 析构函数
*/
GPIO_t::~GPIO_t()
{
    // Nothing to do here
}

/**
 * @brief 打开引脚
*/
void GPIO_t::on()
{
    if (this->pwm_flag)
    {
        ledcSetup(this->pwm_channel, this->pwm_freq, this->pwm_resolution);
        ledcAttachPin(this->pin, this->pwm_channel);
        ledcWrite(this->pwm_channel, this->pwm_duty);
    }
    else
    {
        digitalWrite(this->pin, LED_ON);
    }
}

/**
 * @brief 关闭引脚
*/
void GPIO_t::off()
{
    if (this->pwm_flag)
    {
        ledcWrite(this->pwm_channel, 0);
    }
    else
    {
        digitalWrite(this->pin, LED_OFF);
    }
}


/**
 * @brief 设置引脚
 * @param pin 引脚
*/
void GPIO_t::set_pin(uint8_t pin)
{
    this->off();    // 关闭引脚
    this->pin = pin;
}

/**
 * @brief 设置 PWM 通道
 * @param pwm_channel PWM 通道
*/

void GPIO_t::set_pwm_channel(uint8_t pwm_channel)
{   
    this->pwm_channel = pwm_channel;
    ledcWrite(pwm_channel, 0);
    ledcDetachPin(this->pin);

    ledcSetup(pwm_channel, this->pwm_freq, this->pwm_resolution);
    ledcAttachPin(this->pin, pwm_channel);
    ledcWrite(pwm_channel, this->pwm_duty);
}

/**
 * @brief 设置 PWM 占空比
 * @param duty 占空比
*/
void GPIO_t::set_pwm_duty(uint32_t duty)
{
    this->pwm_duty = duty;

    ledcWrite(this->pwm_channel, duty);
}

/**
 * @brief 设置 PWM 分辨率
 * @param resolution 分辨率
*/
void GPIO_t::set_pwm_resolution(uint8_t resolution)
{
    this->pwm_resolution = resolution;

    ledcSetup(this->pwm_channel, this->pwm_freq, resolution);
    ledcWrite(this->pwm_channel, this->pwm_duty);
}

/**
 * @brief 设置 PWM 频率
 * @param freq 频率
*/

void GPIO_t::set_pwm_freq(uint32_t freq)
{
    this->pwm_freq = freq;

    ledcSetup(this->pwm_channel, freq, this->pwm_resolution);
    ledcWrite(this->pwm_channel, this->pwm_duty);
}

/**
 * @brief 获取引脚状态
 * @return 引脚状态
*/
bool GPIO_t::get_pinState()
{
    return digitalRead(this->pin);
}

/**
 * @brief 获取引脚
 * @return 引脚
*/
uint8_t GPIO_t::get_pin()
{
    return this->pin;
}

/**
 * @brief 获取 PWM 通道
 * @return PWM 通道
*/
uint8_t GPIO_t::get_pwm_channel()
{
    return this->pwm_channel;
}

/**
 * @brief 获取 PWM 占空比
 * @return PWM 占空比
*/
uint32_t GPIO_t::get_pwm_duty()
{
    return this->pwm_duty;
}

/**
 * @brief 获取 PWM 分辨率
 * @return PWM 分辨率
*/
uint8_t GPIO_t::get_pwm_resolution()
{
    return this->pwm_resolution;
}

/**
 * @brief 获取 PWM 频率
 * @return PWM 频率
*/
uint32_t GPIO_t::get_pwm_freq()
{
    this->pwm_freq = ledcReadFreq(this->pwm_channel);
    return this->pwm_freq;
}
