// ==================== includes ====================

#include "main.h"

// ==================== global variables ====================

String str_lcd = "";
String str_uart = "";

static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

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

    xl9555_io_config(KEY0, IO_SET_INPUT);
    xl9555_io_config(KEY1, IO_SET_INPUT);
    xl9555_io_config(KEY2, IO_SET_INPUT);
    xl9555_io_config(KEY3, IO_SET_INPUT);

    xl9555_init();          /* IO扩展芯片初始化 */
    lcd_init();             /* LCD初始化 */

    freertos_init();

    lv_init();    // 初始化LVGL

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /*Initialize the display*/
    static lv_disp_t disp;

    static lv_disp_drv_t *disp_drv = disp.driver;
    lv_disp_drv_init(disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv->hor_res = screenWidth;
    disp_drv->ver_res = screenHeight;
    disp_drv->flush_cb = my_disp_flush;
    disp_drv->draw_buf = &draw_buf;
    lv_disp_drv_register( disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

    // uncomment one of these demos 取消注释这些演示之一
    lv_demo_widgets();            // OK
    // lv_demo_benchmark();          // OK
    // lv_demo_keypad_encoder();     // works, but I haven't an encoder
    // lv_demo_music();              // NOK
    // lv_demo_printer();
    // lv_demo_stress();             // seems to be OK
}

/**
 * @brief 主循环
*/
void loop() 
{
    //LED_root();
    DNS_request_loop(); // DNS服务请求处理
}

// ==================== LVGL 相关 ==================== 

void my_disp_flush( _lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    lcd_fill( area->x1, area->y1, area->x2, area->y2, color_p->full);

    lv_disp_flush_ready( disp_drv );
}

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    bool leftKey = (IO_SET_HIGH == xl9555_get_pin(KEY0)) ? true : false;
    bool rightKey = (IO_SET_HIGH == xl9555_get_pin(KEY1)) ? true : false;
    bool upKey = (IO_SET_HIGH == xl9555_get_pin(KEY2)) ? true : false;
    bool downKey = (IO_SET_HIGH == xl9555_get_pin(KEY3)) ? true : false;

    if(leftKey)
    {
        data->key = LV_KEY_LEFT;
        log_now("[INFO] left key pressed");
    }
    else if(rightKey)
    {
        data->key = LV_KEY_RIGHT;
        log_now("[INFO] right key pressed");
    }
    else if(upKey)
    {
        data->key = LV_KEY_UP;
        log_now("[INFO] up key pressed");
    }
    else if(downKey)
    {
        data->key = LV_KEY_DOWN;
        log_now("[INFO] down key pressed");
    }
    else
    {

    }
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

