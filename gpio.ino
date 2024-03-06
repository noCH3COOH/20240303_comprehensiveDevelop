#include "global.h"

#define LED_PIN 1 // 定义LED引脚

/**
 * @brief 初始化GPIO
*/
void GPIO_init()
{
    pinMode(LED_PIN, OUTPUT); // 引脚2设置为输出模式
    digitalWrite(LED_PIN, 0); // 引脚2输出低电平
}  

///**
// * @brief 设置GPIO
// * @param request 请求
//*/  
//void GPIO_button(AsyncWebServerRequest *request)
//{  
//    int pin_state = !digitalRead(1);
//    String state;
//    digitalWrite(1, pin_state); // 每次按下循环地改变引脚状态
//    if (pin_state)
//    {
//      state = "开";
//    }
//    else
//    {
//      state = "关";
//    }
//    request->send(200, "text/plain", state); // 把状态发送回页面
//    Serial.print("引脚状态改变为:");
//    Serial.println(pin_state);
//}

/**
 * @brief 读取 LED PWM数值
*/
void LED_read(AsyncWebServerRequest *request)
{
    int pwm = analogRead(LED_PIN);
    pwm = (int)(pwm / 10.23);
    request->send(200, "text/plain", String(pwm) + "%");
    String print_str = "LED PWM数值: " + String(pwm) + "%";
    Serial.println(print_str);
}

/**
 * @brief 设置 LED PWM数值
 * @param request 请求
*/
void LED_write(AsyncWebServerRequest *request)
{
    String pwm = request->arg("LED_pwm");
    int pwm_value = pwm.toInt();
    pwm_value = (int)(pwm_value * 2.55);

    analogWrite(LED_PIN, pwm_value);
    delay(500);

    String print_str = "设置LED PWM数值为: " + pwm + "%" + String(pwm_value);
    Serial.println(print_str);
    request->send(200, "text/plain", "OK");
}
