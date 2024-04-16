#ifndef __FILE_SYSTEM_H
#define __FILE_SYSTEM_H

// ==================== includes ====================

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#include "log.h"

// ==================== struct ====================

struct CONFIG
{
    String wifiname;
    String wifipassword;
    String ip;
    String AP_ip;
    const String AP_ssid;
};

// ==================== global variables ====================

extern struct CONFIG global_config;

// ==================== functions ====================

bool str2file(String path, String str);
String file2str(String path);
String analysis_json(String str, String Name);

void LittleFS_begin();
void update_config();

#endif   // __FILE_SYSTEM_H
