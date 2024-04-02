#include "dht11.h"

// ==================== global variables ====================

float dht11_temp_his[HIS_LEN] = {20, 0, 0};
float dht11_humi_his[HIS_LEN] = {20, 0, 0};

DHT dht11(DHT_PIN, DHT11);

// ===================== functions =====================

/**
 * @brief 计算平均值
 * @param num 数量
 * @param tar 目标数组
*/
float average(int num, float* tar)
{
    float sum = 0;

    for(int i = 0; i < num; i++) sum += tar[i];

    return sum / num;
}

/**
 * @brief 初始化DHT11
*/
bool dht11_init()
{
    short init_time = 0;

    dht11.begin();
    while(init_time < HIS_LEN && dht11_getData()) { init_time += 1; }
    
    if(init_time < HIS_LEN) return false;
    else return true;
}

/**
 * @brief 获取温湿度数据
 * @return bool 是否成功
*/
bool dht11_getData()
{
    float store_temp = 0;
    float store_humi = 0;

    short try_time = 0;

    do{
        store_temp = check_appoarh(dht11.readTemperature(), dht11_temp_his[0], 50);
        store_humi = check_appoarh(dht11.readHumidity(), dht11_humi_his[0], 50);
        delayNoBlock_ms(250);

        if(isnan(store_temp) ||  isnan(store_humi) ) 
            try_time += 1;
        else
            break;

    }while(try_time <= 3);
    if(try_time > 3)
    {
        return false;
    }

    slide_dataHis(dht11_temp_his);
    slide_dataHis(dht11_humi_his);

    dht11_temp_his[0] = store_temp;
    dht11_humi_his[0] = store_humi;

    return true;
}

/**
 * @brief 获取温度，对外接口
 * @return float 温度
*/
float dht11_getTemp()
{
    return average(HIS_LEN, dht11_temp_his);
}

/**
 * @brief 获取湿度，对外接口
 * @return float 湿度
*/
float dht11_getHumi()
{
    return average(HIS_LEN, dht11_humi_his);
}

/**
 * @brief 读取温度
 * @param request 请求
*/
void getCallback_readTemp(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", String(dht11_getTemp()) + "°C");
}

/**
 * @brief 读取湿度
 * @param request 请求
*/
void getCallback_readWet(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", String(dht11_getHumi()) + "%");
}
