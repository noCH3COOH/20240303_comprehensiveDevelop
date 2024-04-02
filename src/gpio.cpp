#include "gpio.h"

// ==================== global variables ====================

GPIO_t led(BRIGHTNESS_CTRL_LED_PIN);

int loop_duty = 0;
bool loop_direation = true;

// ==================== functions ====================

/**
 * @brief 初始化 LED
*/
void LED_init()
{
    led.set_mode_pwm(BRIGHTNESS_CTRL_LED_CHANNEL, 5000, 10, 50);
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
    const String str_request = String(std::to_string(led.get_pwm_duty().data).c_str()) + "%";
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
        led.set_pwm_duty(LED_duty);
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
    this->pin_mode = 0;
    this->pin_count = 0;

    this->pwm_channel = 0;
    this->pwm_duty = 0;
    this->pwm_resolution = 0;
    this->pwm_freq = 0;

    this->pwm_flag = false;
}

/**
 * @brief GPIO 构造函数
 * @param pin 引脚
*/
GPIO_t::GPIO_t(uint8_t pin)
{
    this->pin[0] = pin;
    this->pin_count = 1;
    this->pin_mode = 0;

    this->pwm_channel = 0;
    this->pwm_duty = 0;
    this->pwm_resolution = 0;
    this->pwm_freq = 0;

    this->pwm_flag = false;
    this->adc_flag = false;
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
GPIO_t_retval<bool> GPIO_t::on()
{
    if (this->pwm_flag)
    {
        ledcSetup(this->pwm_channel, this->pwm_freq, this->pwm_resolution);
        for(int i=0; i<(this->pin_count); i++)
            ledcAttachPin(this->pin[i], this->pwm_channel);
        ledcWrite(this->pwm_channel, PWM_CALC(this->pwm_duty * 10.23));
    }
    else if(this->adc_flag)
    {
        for(int i=0; i<(this->pin_count); i++)
            pinMode(this->pin[i], INPUT);
    }
    else
    {
        for(int i=0; i<(this->pin_count); i++)
            digitalWrite(this->pin[0], LED_ON);
    }

    return {true, GPIO_t_OK};
}

/**
 * @brief 关闭引脚
*/
GPIO_t_retval<bool> GPIO_t::off()
{
    if (this->pwm_flag)
    {
        ledcWrite(this->pwm_channel, 0);
    }
    else
    {
        for(int i=0; i<(this->pin_count); i++)
            digitalWrite(this->pin[i], LED_OFF);
    }

    return {true, GPIO_t_OK};
}

/**
 * @brief 添加引脚
 * @param pin 引脚
 * @return 是否添加成功
 * @note GPIO_t_OK 添加成功
 * @note GPIO_t_ERROR 添加失败，可能有重复引脚
*/
GPIO_t_retval<bool> GPIO_t::add_pin(uint8_t pin)
{
    for(int i=0; i<(this->pin_count); i++)
    {
        if (this->pin[i] == pin)
            return {false, GPIO_t_ERROR};
    }
    
    this->pin[this->pin_count] = pin;
    this->pin_count++;

    if(this->pwm_flag)
    {
        ledcSetup(this->pwm_channel, this->pwm_freq, this->pwm_resolution);
        ledcAttachPin(pin, this->pwm_channel);
        ledcWrite(this->pwm_channel, PWM_CALC(this->pwm_duty * 10.23));
    }
    else
        pinMode(pin, this->pin_mode);

    return {true, GPIO_t_OK};
}

/**
 * @brief 删除引脚
 * @param pin 引脚
 * @return 是否删除成功
 * @note GPIO_t_OK 删除成功
 * @note GPIO_t_ERROR 删除失败
*/
GPIO_t_retval<bool> GPIO_t::delete_pin(uint8_t pin)
{
    for(int i=0; i<(this->pin_count); i++)
    {
        if (this->pin[i] == pin)
        {
            for(int j=i; j<this->pin_count-1; j++)
                this->pin[j] = this->pin[j+1];
            this->pin_count--;

            if(this->pwm_flag)
                ledcDetachPin(pin);

            return {true, GPIO_t_OK};
        }
    }
    return {false, GPIO_t_ERROR};
}

/**
 * @brief 设置模式
*/
GPIO_t_retval<bool> GPIO_t::set_mode(uint8_t pin_mode)
{
    this->pin_mode = pin_mode;

    for(int i=0; i<(this->pin_count); i++)
        pinMode(this->pin[i], pin_mode);
    
    return {true, GPIO_t_OK};
}

GPIO_t_retval<bool> GPIO_t::set_mode_pwm(uint8_t pwm_channel, uint32_t freq, uint8_t resolution, uint8_t duty)
{
    this->pwm_channel = pwm_channel;
    this->pwm_freq = freq;
    this->pwm_resolution = resolution;
    this->pwm_duty = duty;

    ledcSetup(this->pwm_channel, this->pwm_freq, this->pwm_resolution);
    
    for(int i=0; i<(this->pin_count); i++)
        ledcAttachPin(this->pin[i], this->pwm_channel);
    
    ledcWrite(this->pwm_channel, PWM_CALC(this->pwm_duty * 10.23));

    return {true, GPIO_t_OK};
}

GPIO_t_retval<bool> GPIO_t::set_mode_adc()
{
    for(int i=0; i<(this->pin_count); i++)
        pinMode(this->pin[i], INPUT);
    
    return {true, GPIO_t_OK};
}


/**
 * @brief 设置 PWM 通道
 * @param pwm_channel PWM 通道
*/
GPIO_t_retval<bool> GPIO_t::set_pwm_channel(uint8_t pwm_channel)
{   
    this->pwm_channel = pwm_channel;

    ledcWrite(pwm_channel, 0);
    
    for(int i=0; i<(this->pin_count); i++)
        ledcDetachPin(this->pin[i]);

    ledcSetup(pwm_channel, this->pwm_freq, this->pwm_resolution);
    
    for(int i=0; i<(this->pin_count); i++)
        ledcAttachPin(this->pin[i], pwm_channel);
    
    ledcWrite(pwm_channel, PWM_CALC(this->pwm_duty * 10.23));

    return {true, GPIO_t_OK};
}

/**
 * @brief 设置 PWM 占空比
 * @param duty 占空比
*/
GPIO_t_retval<bool> GPIO_t::set_pwm_duty(uint8_t duty)
{
    this->pwm_duty = duty;

    ledcWrite(this->pwm_channel, PWM_CALC(duty * 10.23));

    return {true, GPIO_t_OK};
}

/**
 * @brief 设置 PWM 分辨率
 * @param resolution 分辨率
*/
GPIO_t_retval<bool> GPIO_t::set_pwm_resolution(uint8_t resolution)
{
    this->pwm_resolution = resolution;

    ledcSetup(this->pwm_channel, this->pwm_freq, resolution);
    ledcWrite(this->pwm_channel, PWM_CALC(this->pwm_duty * 10.23));

    return {true, GPIO_t_OK};
}

/**
 * @brief 设置 PWM 频率
 * @param freq 频率
*/

GPIO_t_retval<bool> GPIO_t::set_pwm_freq(uint32_t freq)
{
    this->pwm_freq = freq;

    ledcSetup(this->pwm_channel, freq, this->pwm_resolution);
    ledcWrite(this->pwm_channel, PWM_CALC(this->pwm_duty * 10.23));

    return {true, GPIO_t_OK};
}

/**
 * @brief 获取引脚状态
 * @param pin 引脚 
 * @return 引脚状态
 * @note {占空比, GPIO_t_OK} PWM
 * @note {1/0, GPIO_t_OK} plain引脚
 * @note {-1, GPIO_t_ERROR} 失败
*/
GPIO_t_retval<int8_t> GPIO_t::get_pinState(uint8_t pin)
{
    for(int i=0; i<(this->pin_count); i++)
    {
        if(pin != this->pin[i])
            continue;
        else
        {
            if (this->pwm_flag)
            {
                int8_t read_duty = PWM_CALC(ledcRead(this->pwm_channel)) / 10.23;
                if (read_duty > 0)
                    return {read_duty, GPIO_t_OK};
                else
                    return {0, GPIO_t_OK};
            }
            else
            {
                if(LED_ON == digitalRead(pin))
                    return {1, GPIO_t_OK};
                else
                    return {0, GPIO_t_OK};
            }
        }
    }

    return {-1, GPIO_t_ERROR};
}

/**
 * @brief 获取引脚
 * @param index 索引
 * @return 引脚
*/
GPIO_t_retval<uint8_t> GPIO_t::get_pin(uint8_t index)
{
    return {this->pin[index], GPIO_t_OK};
}

/**
 * @brief 获取 PWM 分辨率
 * @return PWM 分辨率
*/
GPIO_t_retval<uint8_t> GPIO_t::get_pwm_resolution()
{
    return {this->pwm_resolution, GPIO_t_OK};
}

/**
 * @brief 获取 PWM 通道
 * @return PWM 通道
*/
GPIO_t_retval<uint8_t> GPIO_t::get_pwm_channel()
{
    return {this->pwm_channel, GPIO_t_OK};
}

/**
 * @brief 获取 PWM 占空比
 * @return PWM 占空比
*/
GPIO_t_retval<uint8_t> GPIO_t::get_pwm_duty()
{
    return {this->pwm_duty, GPIO_t_OK};
}

/**
 * @brief 获取 PWM 频率
 * @return PWM 频率
*/
GPIO_t_retval<uint32_t> GPIO_t::get_pwm_freq()
{
    this->pwm_freq = ledcReadFreq(this->pwm_channel);

    return {this->pwm_freq, GPIO_t_OK};
}
