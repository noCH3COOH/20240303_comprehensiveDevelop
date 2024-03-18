#include "global.h"

void setup()
{
    Serial.begin(115200); // 串口波特率初始化
    LittleFS_begin();   // LittleFS文件系统初始化
    connect_NET();      // 网络初始化
    web_server();       // WEB服务器初始化
    GPIO_init();

    dht11_humidity = -1;
    dht11_temperature = -1;
}

void loop()
{
    DNS_request_loop(); // DNS服务请求处理

    //LED_root();
}