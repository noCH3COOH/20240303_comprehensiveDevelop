#include "global.h"

bool dht11_getData(void)
{
    dht11_humidity = dht.readHumidity();
    dht11_temperature = dht.readTemperature();

    String print_str = "获取湿度" + String(dht11_humidity);
    print_str += " 获取温度" +  String(dht11_temperature) + "°C";
    Serial.println(print_str);
}
