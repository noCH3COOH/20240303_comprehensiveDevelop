#include "global.h"

/**
 * @brief 初始化GPIO
*/
void GPIO_init()
{
    pinMode(1, OUTPUT); // 引脚2设置为输出模式
}  

/**
 * @brief 设置GPIO
 * @param request 请求
*/  
void GPIO_button(AsyncWebServerRequest *request)
{  
    int pin_state = !digitalRead(1);
    String state;
    digitalWrite(1, pin_state); // 每次按下循环地改变引脚状态
    if (pin_state)
    {
      state = "开";
    }
    else
    {
      state = "关";
    }
    request->send(200, "text/plain", state); // 把状态发送回页面
    Serial.print("引脚状态改变为:");
    Serial.println(pin_state);
}
