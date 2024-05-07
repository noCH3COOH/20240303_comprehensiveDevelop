// ==================== includes ====================

#include "main.h"

// ==================== global variables ====================

String str_lcd = "";
String str_uart = "";

static const uint16_t screenWidth  = TFT_WIDTH;
static const uint16_t screenHeight = TFT_HEIGHT;

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ LVGL_BUF_SIZE ];

uint32_t frame_time = 0;

float adc_in = 0;

// ==================== 业务 ====================

/**
 * @brief 初始化
*/
void setup() 
{ 
    log_init();

    log_now("[INFO] 内部 RAM 空闲大小：" + String(heap_caps_get_free_size(MALLOC_CAP_DEFAULT)));
    log_now("[INFO] PSRAM 空闲大小：" + String(heap_caps_get_free_size(MALLOC_CAP_SPIRAM)));
    
    LittleFS_begin();   // LittleFS文件系统初始化
    init_network();      // 网络初始化
    init_webServer();       // WEB服务器初始化

    log_now(dht11_init() ? "[SUCCESS] 温度计初始化完成" : "[ERROR] 温度计初始化失败");    // 温湿度传感器初始化

    log_now("[INFO] 初始化 IO 接口");
    {
        GPIO_init();
        pinMode(ADC_PIN, INPUT);
    }
    log_now("[SUCCESS] IO 接口初始化完成");

    log_now("[INFO] LCD初始化...");
    {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(TFT_DARKGREY);

        tft.setCursor(10, 10);
        tft.setTextSize(2);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);

        // for(int i=0; i<16; i++)
        // {
        //     tft.fillScreen(default_4bit_palette[i]);
        //     delayNoBlock_ms(300);
        // }
    }
    log_now("[SUCCESS] LCD初始化完成");

    log_now("[INFO] 触摸屏初始化...");
    {
        XPT2046_touchInit();
        XPT2046_setRotation(XPT_ROTATE_90);
    }
    log_now("[SUCCESS] 触摸屏初始化成功");

    log_now("[INFO] 初始化LVGL...");
    {
        lvgl_init();
        ui_init();
        lv_obj_add_event_cb(ui_fresh_Label, ui_event_freshLabel, LV_EVENT_REFRESH, NULL);
    }
    log_now("[SUCCESS] LVGL初始化完成");

    log_now("[INFO] 初始化游戏...");
    {
        game_init();    // 游戏初始化
    }
    log_now("[SUCCESS] 游戏初始化完成");

    freertos_init();    // FreeRTOS初始化
    log_now("[SUCCESS] 初始化完成，开始任务调度");
}

/**
 * @brief 主循环
 */
void loop()
{
    led.set_pwm_duty(100 - (adc_in / 4095.0 * 100));
    if(isAP)    DNS_request_loop(); // DNS服务请求处理
}

// ==================== LVGL 相关 ====================

void lvgl_init()
{
    lv_init(); // 初始化LVGL

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LVGL_BUF_SIZE);

    /*Initialize the display*/

    static lv_disp_drv_t *disp_drv;
    disp_drv = (lv_disp_drv_t *)malloc(sizeof(lv_disp_drv_t));
    lv_disp_drv_init(disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv->hor_res = screenHeight;
    disp_drv->ver_res = screenWidth;
    disp_drv->flush_cb = my_disp_flush;
    disp_drv->draw_buf = &draw_buf;
    lv_disp_drv_register(disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

void my_disp_flush(_lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    XPT2046_retval_t ts_p = XPT2046_getTouch();
    
    if(ts_p.ret)
    {
        data->state = LV_INDEV_STATE_PR;

        (data->point).x = ts_p.point.x;
        (data->point).y = ts_p.point.y;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}


void ui_event_freshLabel(lv_event_t * e)
{
    lv_label_set_text(ui_tempLabel, (String(dht11_getTemp()) + "°C").c_str());
    lv_label_set_text(ui_brightLabel, (String(int(adc_in / 4095.0 * 100)) + "%").c_str());
    lv_label_set_text(ui_wetLabel, (String(dht11_getHumi()) + "%").c_str());
    lv_label_set_text(ui_bombLabel, (String(led.get_pwm_duty().data) + "%").c_str());
    lv_label_set_text(ui_wifiLabel, (global_config.wifiname).c_str());
    lv_label_set_text(ui_ipLabel, (global_config.ip).c_str());
    
    if(!isAP)
        lv_label_set_text(ui_hotpotLabel, "未配网");
}

// ==================== freertos 相关 ==================== 

/**
 * @brief FreeRTOS初始化
*/
void freertos_init()
{
    xTaskCreatePinnedToCore(task_feed, "task_feed_core1", (1*1024), NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(task_lvgl, "task_lvgl", (6*1024), NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(task_feed, "task_feed_core2", (1*1024), NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(task_game, "task_game", (2*1024), NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(task_sensor_getData, "task_sensor_getData", (4*1024), NULL, 2, NULL, 1);
}

/**
 * @brief 喂狗任务
 * @param pvParameters 任务参数
*/
void task_feed(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
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
        lv_timer_handler();    // LVGL定时器处理
        vTaskDelay(5 / portTICK_PERIOD_MS);

        lv_event_send(ui_fresh_Label, LV_EVENT_REFRESH, NULL);
    }
    log_now("[INFO] Ending task_lvgl");
    vTaskDelete(NULL);
}

/**
 * @brief FreeRTOS任务2
 * @param pvParameters 任务参数
 * @note 任务2，游戏任务
*/
void task_game(void *pvParameters)
{
    while(1)
    {
        game_loop();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

/**
 * @brief FreeRTOS任务3
 * @param pvParameters 任务参数
 * @note 任务3，获取传感器数据
*/
void task_sensor_getData(void *pvParameters)
{
    while(1)
    {
        // log_now("[INFO] task_dht11_getData running");

        dht11_getData();
        adc_in = analogRead(ADC_PIN);

        // str_uart = "[INFO] Temp: " + String(dht11_getTemp()) + "°C Humi: " + String(dht11_getHumi()) + "%";
        // log_now(str_uart);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    log_now("[INFO] Ending task_dht11_getData");
    vTaskDelete(NULL);
}
