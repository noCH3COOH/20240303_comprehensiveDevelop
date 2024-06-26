#ifndef __MAIN_H
#define __MAIN_H

// ==================== includes ====================

#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include <DNSServer.h>

#include "log.h"
#include "delayNoBlock.h"

#include "gpio.h"
#include "dht11.h"
#include "file_system.h"
#include "web_server.h"

#include "TFT_eSPI.h"
#include "xpt2046.h"

#include "lvgl.h"
#include "ui.h"

#include "game.h"

// ==================== defines ====================

#define LVGL_BUF_SIZE (screenWidth * screenHeight) / 10

#define TS_SDO_PIN 4
#define TS_SDI_PIN 6
#define TS_CS_PIN 15
#define TS_CLK_PIN 17

#define ADC_PIN 18

// ==================== global variables ====================

extern String str_lcd;
extern String str_uart;

// ==================== functions ====================

void setup();
void loop();

void lvgl_init();
void my_disp_flush( _lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p );
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
void ui_event_freshLabel(lv_event_t * e);

void freertos_init();

void task_feed(void *pvParameters);
void task_lvgl(void *pvParameters);
void task_game(void *pvParameters);
void task_sensor_getData(void *pvParameters);

#endif    // __MAIN_H
