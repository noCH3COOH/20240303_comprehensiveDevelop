#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <DHT.h>
#include <DHT_U.h>

#include "xl9555.h"
#include "spilcd.h"
#include "alientek_logo.h"
#include "demo_show.h"

// 定义LED引脚
#define WORK_LED_CHANNEL 0
#define LED_PIN 1

#define BRIGHTNESS_CTRL_LED_CHANNEL 1
#define LED1_PIN 5
#define LED2_PIN 7
#define LED3_PIN 16
#define LED4_PIN 18

#define DHT_PIN 0

#define delayNoBlock_us(us) { \
        unsigned long perviousTime, currentTime = micros(); \
        do { perviousTime = micros(); } while((perviousTime - currentTime) < us); \
    }

#define delayNoBlock_ms(ms) { \
        unsigned long perviousTime, currentTime = millis(); \
        do { perviousTime = millis(); } while((perviousTime - currentTime) < ms); \
    }

struct CONFIG
{
    String wifiname = "";
    String wifipassword = "";
    String ip = "";
    String AP_ip = "";
    const String AP_ssid = "esp32_AP";
    const String AP_password = "12345678";
    const String AP_url = "ESPAP.com";
};

struct CONFIG global_config;

int onBoard_LED_duty;
bool onBoard_LED_up;

float dht11_temperature = -1;
float dht11_humidity = -1;

AsyncWebServer server(80); // 创建一个服务器对象，WEB服务器端口:80
DNSServer dnsserver;

DHT dht(DHT_PIN, DHT11);

#endif
