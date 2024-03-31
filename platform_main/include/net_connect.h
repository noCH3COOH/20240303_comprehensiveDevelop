#ifndef __NET_CONNECT_H
#define __NET_CONNECT_H

// =========================== includes ===========================

#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include "ESPAsyncWebServer.h"

#include "log.h"
#include "delayNoBlock.h"
#include "file_system.h"

// =========================== global variables ===========================

extern AsyncWebServer server;
extern DNSServer dnsserver;

// =========================== functions ===========================

void connect_WIFI(String ssid, String password);
void connect_NET();
void DNS_request_loop();
void getCallback_readWIFI(AsyncWebServerRequest *request);
void getCallback_readIP(AsyncWebServerRequest *request);
void getCallback_readAPip(AsyncWebServerRequest *request);

#endif    // __NET_CONNECT_H
