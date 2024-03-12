#include "global.h"

int onBoard_LED_duty;
bool onBoard_LED_up;

/**
 * @brief 初始化GPIO
*/
void GPIO_init()
{
    ledcSetup(WORK_LED_CHANNEL, 5000, 10);
    ledcAttachPin(LED_PIN, WORK_LED_CHANNEL);

    ledcSetup(BRIGHTNESS_CTRL_LED_CHANNEL, 5000, 10);
    ledcAttachPin(LED1_PIN, BRIGHTNESS_CTRL_LED_CHANNEL);
    ledcAttachPin(LED2_PIN, BRIGHTNESS_CTRL_LED_CHANNEL);
    ledcAttachPin(LED3_PIN, BRIGHTNESS_CTRL_LED_CHANNEL);
    ledcAttachPin(LED4_PIN, BRIGHTNESS_CTRL_LED_CHANNEL);

    onBoard_LED_duty = 0;
    onBoard_LED_up = true;
}  

/**
 * @brief 测试LED
*/
void LED_root()
{
    if(onBoard_LED_up)
        onBoard_LED_duty += 2;
    else
        onBoard_LED_duty -= 2;
    
    ledcWrite(WORK_LED_CHANNEL, onBoard_LED_duty);

    if(onBoard_LED_duty >= 1023 || onBoard_LED_duty <= 0)
        onBoard_LED_up = !onBoard_LED_up;   

    delay(5);     
}

/**
 * @brief 读取 LED PWM数值
*/
void getCallback_readLED(AsyncWebServerRequest *request)
{
    int LED_duty = (ledcRead(BRIGHTNESS_CTRL_LED_CHANNEL) / 10.23);
    request->send(200, "text/plain", String(LED_duty) + '%');
    
    //String print_str = "LED PWM数值: " + String(LED_duty);
    //Serial.println(print_str);
}

/**
 * @brief 设置 LED PWM数值
 * @param request 请求
*/
void postCallback_setLED(AsyncWebServerRequest *request)
{
    String pwm = request->arg("LED_pwm");
    int LED_duty = (pwm.toInt() * 10.23);

    for(int i=0; i<8; i++)
    {
        ledcWrite(BRIGHTNESS_CTRL_LED_CHANNEL, LED_duty);
        delay(15);
    }
    delay(500);

    String print_str = "设置LED PWM数值为: " + pwm + "% (" + String(LED_duty) + ')';
    Serial.println(print_str);
    request->send(200, "text/plain", "OK");
}
