#ifndef __MAIN_H
#define __MAIN_H

// ==================== includes ====================

#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include <DNSServer.h>

#include "log.h"
#include "delayNoBlock.h"

#include "xl9555.h"
#include "spilcd.h"
#include "demo_show.h"
#include "alientek_logo.h"

#include "gpio.h"
#include "dht11.h"
#include "file_system.h"
#include "net_connect.h"
#include "web_server.h"

// ==================== defines ====================

// ==================== global variables ====================

extern String str_lcd;
extern String str_uart;

// ==================== functions ====================

void setup();
void loop();

void freertos_init();
void freertos_task1(void *pvParameters);
void freertos_task2(void *pvParameters);
void freertos_task3(void *pvParameters);
void freertos_task4(void *pvParameters);

#endif    // __MAIN_H