// ==================== includes ====================

#include "main.h"

// ==================== global variables ====================

String str_lcd = "";
String str_uart = "";

uint16_t ts_nowPoint_x = 0;
uint16_t ts_nowPoint_y = 0;

//static const uint16_t screenWidth  = 240;
//static const uint16_t screenHeight = 240;

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
XPT2046_Touchscreen ts(TS_CS_PIN);

// static lv_disp_draw_buf_t draw_buf;
// static lv_color_t buf[ LVGL_BUF_SIZE ];

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
    
    xl9555_io_config(KEY0, IO_SET_INPUT);
    xl9555_io_config(KEY1, IO_SET_INPUT);
    xl9555_io_config(KEY2, IO_SET_INPUT);
    xl9555_io_config(KEY3, IO_SET_INPUT);

    //lcd_init();             /* LCD初始化 */
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_DARKGREY);

    tft.setCursor(10, 10);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // lvgl_init();    // LVGL初始化

    short retry = 0;
    while(retry < 3 && (!ts.begin(TS_CLK_PIN, TS_SDI_PIN, TS_SDO_PIN)))
    {
        retry += 1;
        log_now("[ERROR] 触摸屏初始化失败，重试" + String(retry) + "次...");
    }
    if(retry < 3)
        ts.setRotation(1);
    else
        log_now("[ERROR] 触摸屏初始化彻底失败");

    freertos_init();    // FreeRTOS初始化
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

// void lvgl_init()
// {
//     log_now("[INFO] 开始初始化LVGL...");
// 
//     lv_init();    // 初始化LVGL
// 
//     lv_disp_draw_buf_init( &draw_buf, buf, NULL, LVGL_BUF_SIZE );
// 
//     /*Initialize the display*/
// 
//     static lv_disp_drv_t *disp_drv;
//     disp_drv = (lv_disp_drv_t *)malloc(sizeof(lv_disp_drv_t));
//     lv_disp_drv_init(disp_drv);
//     /*Change the following line to your display resolution*/
//     disp_drv->hor_res = screenWidth;
//     disp_drv->ver_res = screenHeight;
//     disp_drv->flush_cb = my_disp_flush;
//     disp_drv->draw_buf = &draw_buf;
//     lv_disp_drv_register( disp_drv );
// 
//     /*Initialize the (dummy) input device driver*/
//     static lv_indev_drv_t indev_drv;
//     lv_indev_drv_init( &indev_drv );
//     indev_drv.type = LV_INDEV_TYPE_KEYPAD;
//     indev_drv.read_cb = my_touchpad_read;
//     lv_indev_drv_register( &indev_drv );
// }
// 
// void my_disp_flush( _lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
// {
//     uint32_t w = ( area->x2 - area->x1 + 1 );
//     uint32_t h = ( area->y2 - area->y1 + 1 );
// 
//     lcd_fill( area->x1, area->y1, area->x2, area->y2, color_p->full);
// 
//     lv_disp_flush_ready( disp_drv );
// }
// 
// void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
// {
//     bool leftKey = (IO_SET_HIGH == xl9555_get_pin(KEY0)) ? true : false;
//     bool rightKey = (IO_SET_HIGH == xl9555_get_pin(KEY1)) ? true : false;
//     bool upKey = (IO_SET_HIGH == xl9555_get_pin(KEY2)) ? true : false;
//     bool downKey = (IO_SET_HIGH == xl9555_get_pin(KEY3)) ? true : false;
// 
//     if(leftKey)
//     {
//         data->key = LV_KEY_LEFT;
//         log_now("[INFO] left key pressed");
//     }
//     else if(rightKey)
//     {
//         data->key = LV_KEY_RIGHT;
//         log_now("[INFO] right key pressed");
//     }
//     else if(upKey)
//     {
//         data->key = LV_KEY_UP;
//         log_now("[INFO] up key pressed");
//     }
//     else if(downKey)
//     {
//         data->key = LV_KEY_DOWN;
//         log_now("[INFO] down key pressed");
//     }
//     else
//     {
// 
//     }
// }

// ==================== freertos 相关 ==================== 

/**
 * @brief FreeRTOS初始化
*/
void freertos_init()
{
    xTaskCreatePinnedToCore(task_feed, "task_feed", (1*1024), NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(task_lvgl, "task_lvgl", (6*1024), NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(task_dht11_getData, "task_dht11_getData", (4*1024), NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(task_lcd_show, "task_lcd_show", (4*1024), NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(task_ts_getData, "task_ts_getData", (4*1024), NULL, 1, NULL, 1);
}

/**
 * @brief 喂狗任务
 * @param pvParameters 任务参数
*/
void task_feed(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    log_now("[INFO] Ending task_feed");
    vTaskDelete(NULL);
}

/**
 * @brief LVGL FreeRTOS任务
 * @param pvParameters 任务参数
*/
void task_lvgl(void *pvParameters)
{
    while(1)
    {
        // lv_timer_handler();    // LVGL定时器处理
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
    log_now("[INFO] Ending task_lvgl");
    vTaskDelete(NULL);
}

/**
 * @brief FreeRTOS任务3
 * @param pvParameters 任务参数
 * @note 任务3，显示温湿度任务
*/
void task_dht11_getData(void *pvParameters)
{
    while(1)
    {
        // log_now("[INFO] task_dht11_getData running");

        dht11_getData();

        str_uart = "[INFO] Temp: " + String(dht11_getTemp()) + "°C Humi: " + String(dht11_getHumi()) + "%";
        log_now(str_uart);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    log_now("[INFO] Ending task_dht11_getData");
    vTaskDelete(NULL);
}

/**
 * @brief LCD 显示任务
 * @param pvParameters 任务参数
*/
void task_lcd_show(void *pvParameters)
{
    while(1)
    {
        // log_now("[INFO] Task4 running");

        str_lcd = "[INFO] Temp: " + String(dht11_getTemp()) + "°C";
        tft.drawString(str_lcd, 10, 10);

        str_lcd = "[INFO] Humi: " + String(dht11_getHumi()) + "%";
        tft.drawString(str_lcd, 10, 42);

        str_lcd = "[INFO] touch: (" + String(ts_nowPoint_x) + ", " + String(ts_nowPoint_y) + ")";
        tft.drawString(str_lcd, 10, 74);
    }
    log_now("[INFO] Ending task_lcd_show");
    vTaskDelete(NULL);
}

/**
 * @brief 触摸屏数据获取任务
 * @param pvParameters 任务参数
*/
void task_ts_getData(void *pvParameters)
{
    while(1)
    {
        // log_now("[INFO] task_ts_getData running");

        TS_Point ts_p = ts.getPoint();
        ts_nowPoint_y = ts_p.y;
        ts_nowPoint_x = ts_p.x;

        str_uart = "[INFO] touch: (" + String(ts_nowPoint_x) + ", " + String(ts_nowPoint_y) + ")";
        log_now(str_uart);

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    log_now("[INFO] Ending task_ts_getData");
    vTaskDelete(NULL);
}

