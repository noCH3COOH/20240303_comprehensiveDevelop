#ifndef GLOBAL_H
#define GLOBAL_H

#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <DHT.h>

// 定义LED引脚
#define WORK_LED_CHANNEL 0
#define LED_PIN 1

#define BRIGHTNESS_CTRL_LED_CHANNEL 1
#define LED1_PIN 5
#define LED2_PIN 7
#define LED3_PIN 16
#define LED4_PIN 18

#define DHT_PIN 0

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

float dht11_humidity;
float dht11_temperature;

AsyncWebServer server(80); // 创建一个服务器对象，WEB服务器端口:80

#endif
