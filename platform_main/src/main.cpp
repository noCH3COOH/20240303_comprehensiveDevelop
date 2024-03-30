#include "main.h"

void setup() 
{
    // put your setup code here, to run once:
    
    LED_init();

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
    // put your main code here, to run repeatedly:
    LED_root();

    demo_show_cube();   /* 演示立方体3D旋转 */
}
