// ==================== includes ====================

#include "main.h"

// ==================== global variables ====================

String str_lcd = "";
String str_uart = "";

// ==================== 业务 ====================

/**
 * @brief 初始化
*/
void setup() 
{ 
    log_init();
    
    LittleFS_begin();   // LittleFS文件系统初始化
    connect_NET();      // 网络初始化
    web_server();       // WEB服务器初始化
    dht11_init();       // 温湿度传感器初始化

    LED_init();

    xl9555_init();          /* IO扩展芯片初始化 */
    lcd_init();             /* LCD初始化 */

    freertos_init();
}

/**
 * @brief 主循环
*/
void loop() 
{
    //LED_root();
    DNS_request_loop(); // DNS服务请求处理
}

// ==================== freertos 相关 ==================== 

/**
 * @brief FreeRTOS初始化
*/
void freertos_init()
{
    xTaskCreate(
            freertos_task1,          /*任务函数*/
            "TaskOne",        /*带任务名称的字符串*/
            10000,            /*堆栈大小，单位为字节*/
            NULL,             /*作为任务输入传递的参数*/
            1,                /*任务的优先级*/
            NULL);            /*任务句柄*/
    xTaskCreate(
            freertos_task2,          /* Task function. */
            "TaskTwo",        /* String with name of task. */
            10000,            /* Stack size in bytes. */
            NULL,             /* Parameter passed as input of the task */
            2,                /* Priority of the task. */
            NULL);            /* Task handle. */
    xTaskCreate(
            freertos_task3,          /* Task function. */
            "taskThree",        /* String with name of task. */
            10000,            /* Stack size in bytes. */
            NULL,             /* Parameter passed as input of the task */
            2,                /* Priority of the task. */
            NULL);            /* Task handle. */
    xTaskCreate(
            freertos_task4,          /* Task function. */
            "taskFour",        /* String with name of task. */
            10000,            /* Stack size in bytes. */
            NULL,             /* Parameter passed as input of the task */
            2,                /* Priority of the task. */
            NULL);            /* Task handle. */
}

/**
 * @brief FreeRTOS任务1
 * @param pvParameters 任务参数
 * @note 任务1，喂狗任务
*/
void freertos_task1(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    log_now("[INFO] Ending Task1");
    vTaskDelete(NULL);
}

/**
 * @brief FreeRTOS任务2
 * @param pvParameters 任务参数
 * @note 任务2，显示立方体任务
*/
void freertos_task2(void *pvParameters)
{
    while(1)
    {
        demo_show_cube();
    }
    log_now("[INFO] Ending Task2");
    vTaskDelete(NULL);
}

/**
 * @brief FreeRTOS任务3
 * @param pvParameters 任务参数
 * @note 任务3，显示温湿度任务
*/
void freertos_task3(void *pvParameters)
{
    while(1)
    {
        str_lcd = "Temp: " + String(dht11_getTemp()) + "°C";
        lcd_show_string(10, 10, 200, 32, LCD_FONT_32, (char*)(str_lcd.c_str()), RED);

        str_lcd = "Humi: " + String(dht11_getHumi()) + "%";
        lcd_show_string(10, 42, 200, 32, LCD_FONT_32, (char*)(str_lcd.c_str()), RED);

        str_uart = "[INFO] Temp: " + String(dht11_getTemp()) + "°C Humi: " + String(dht11_getHumi()) + "%";
        log_now(str_uart);
    }
    log_now("[INFO] Ending Task3");
    vTaskDelete(NULL);
}

/**
 * @brief FreeRTOS任务4
 * @param pvParameters 任务参数
 * @note 任务4，显示LOG任务
*/
void freertos_task4(void *pvParameters)
{
    while(1)
    {
        dht11_getData();
    }
    log_now("[INFO] Ending Task4");
    vTaskDelete(NULL);
}

