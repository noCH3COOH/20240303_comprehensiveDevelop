#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

// =========================== includes ===========================

#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#include "log.h"
#include "delayNoBlock.h"
#include "file_system.h"

#include "gpio.h"
#include "dht11.h"
#include "net_connect.h"

// =========================== functions ===========================

void postCallback_setWIFI(AsyncWebServerRequest *request);
void web_server();

#endif    // _WEB_SERVER_H
