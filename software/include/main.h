#ifndef __MAIN_H
#define __MAIN_H

// ==================== includes ====================

#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include <DNSServer.h>

#include "log.h"
#include "delayNoBlock.h"

#include "xl9555.h"

#include "gpio.h"
#include "dht11.h"
#include "file_system.h"
#include "net_connect.h"
#include "web_server.h"

#include "TFT_eSPI.h"
#include "XPT2046_Touchscreen.h"

// ==================== defines ====================

#define LVGL_BUF_SIZE (screenWidth * screenHeight) / 10

#define TS_SDO_PIN 4
#define TS_SDI_PIN 6
#define TS_CS_PIN 15
#define TS_CLK_PIN 17

// ==================== global variables ====================

extern String str_lcd;
extern String str_uart;

// ==================== functions ====================

void setup();
void loop();

// void lvgl_init();
// void my_disp_flush( _lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p );
// void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );

void freertos_init();

void task_feed(void *pvParameters);
void task_lvgl(void *pvParameters);
void task_dht11_getData(void *pvParameters);
void task_lcd_show(void *pvParameters);
void task_ts_getData(void *pvParameters);

#endif    // __MAIN_H
