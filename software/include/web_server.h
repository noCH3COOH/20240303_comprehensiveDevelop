#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

// =========================== includes ===========================

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include "ESPAsyncWebServer.h"

#include "log.h"
#include "delayNoBlock.h"
#include "file_system.h"

#include "gpio.h"
#include "dht11.h"

// =========================== global variables ===========================

extern DNSServer dnsserver;
extern bool isAP;

// =========================== functions ===========================

void init_webServer();
void init_network();

void connect_WIFI(String ssid, String password);

String set_net_AP();

bool scan_wifi();

void DNS_request_loop();
void dnsCallback_APnetSet();

void callback_APnetSet(AsyncWebServerRequest *request);

void postCallback_setWIFI_AP(AsyncWebServerRequest *request);
void postCallback_setWIFI(AsyncWebServerRequest *request);

void getCallback_readWIFI(AsyncWebServerRequest *request);
void getCallback_readIP(AsyncWebServerRequest *request);
void getCallback_readAPip(AsyncWebServerRequest *request);

#endif    // _WEB_SERVER_H
