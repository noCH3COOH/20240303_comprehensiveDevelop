#include "global.h"

void setup()
{
    Serial.begin(115200); // 串口波特率初始化
    LittleFS_begin();   // LittleFS文件系统初始化
    connect_NET();      // 网络初始化
    web_server();       // WEB服务器初始化
    //GPIO_init();        // GPIO初始化
    dht.begin();

    xl9555_init();          /* IO扩展芯片初始化 */
    lcd_init();             /* LCD初始化 */

    /* 刷屏测试 */
    lcd_clear(BLACK);
    delay(500);
    lcd_clear(RED);
    delay(500);
    lcd_clear(GREEN);
    delay(500);
    lcd_clear(BLUE);
    delay(500);
    lcd_clear(YELLOW);
    delay(500);
    lcd_clear(WHITE);
    delay(500);

    lcd_show_pic(0, 0, 240, 82, ALIENTEK_LOGO);                           /* LCD显示ALIENTEK图片 */
    lcd_show_string(10, 100, 200, 32, LCD_FONT_32, "ESP32-S3", RED);      /* LCD显示32号字体ESP32S3 */
    lcd_show_string(10, 132, 200, 24, LCD_FONT_24, "TFTLCD TEST", RED);   /* LCD显示24号字体TFTLCD TEST */
    lcd_show_string(10, 156, 200, 16, LCD_FONT_16, "ATOM@ALIENTEK", RED); /* LCD显示16号字体ATOM@ALIENTEK */
    delay(500);
}

void loop()
{
    DNS_request_loop(); // DNS服务请求处理

    dht11_getData();

    demo_show_cube();   /* 演示立方体3D旋转 */
}N