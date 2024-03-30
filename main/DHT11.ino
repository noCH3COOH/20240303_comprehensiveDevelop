#include "global.h"

// ========== 业务层 ==========

void getCallback_readTemp(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", String(dht11_temperature) + "°C");
}

void getCallback_readWet(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", String(dht11_humidity) + "%");
}
