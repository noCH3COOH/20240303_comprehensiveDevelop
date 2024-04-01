#ifndef __DHT11_H
#define __DHT11_H

// ==================== includes ====================

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include "ESPAsyncWebServer.h"
#include "delayNoBlock.h"

// ==================== defines ====================

#define DHT_PIN 0

#define HIS_LEN 3

#define slide_dataHis(dataHis) { \
                            for(short i = 0, len = (sizeof(dataHis) / sizeof(dataHis[0]) - 1); i < len; i++) \
                            { dataHis[i + 1] = dataHis[i]; } }

#define check_appoarh(x1, x2, max) (abs(x1 - x2) < max ? x1 : x2)

// ==================== global variables ====================

extern float dht11_temp_his[HIS_LEN];
extern float dht11_humi_his[HIS_LEN];

// ===================== functions =====================

float average(int num, float* tar);

bool dht11_init();
bool dht11_getData();

float dht11_getTemp();
float dht11_getHumi();

void getCallback_readTemp(AsyncWebServerRequest *request);
void getCallback_readWet(AsyncWebServerRequest *request);

#endif
