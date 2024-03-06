#include "global.h"

AsyncWebServer server(80); // 创建一个服务器对象，WEB服务器端口:80

void setup()
{
    Serial.begin(115200); // 串口波特率初始化
    LittleFS_begin();   // LittleFS文件系统初始化
    connect_NET();      // 网络初始化
    web_server();       // WEB服务器初始化
    GPIO_init();
}

void loop()
{
    DNS_request_loop(); // DNS服务请求处理
}