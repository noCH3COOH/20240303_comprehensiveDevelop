#include "global.h"

// ========== 业务层 ==========

#define DHT11_DATA_GET() dht11_readData(&dht11_temperature, &dht11_humidity)

bool dht11_getTemp(void)
{
    DHT11_DATA_GET();

    String print_str = "[INFO] 获取温度" +  String(dht11_temperature) + "°C";
    Serial.println(print_str);
    delay(250);
}

bool dht11_getHumidity(void)
{
    DHT11_DATA_GET();

    String print_str = "[INFO] 获取湿度" + String(dht11_humidity);
    Serial.println(print_str);
    delay(250);
}

void getCallback_readTemp(AsyncWebServerRequest *request)
{
    short retry = 0;
    while(retry < 3 && (!dht11_getTemp())) { retry += 1; };

    if(retry < 3)
        request->send(200, "text/plain", String(dht11_temperature) + "°C");
    else
        request->send(200, "text/plain", "ERROR");
}

void getCallback_readWet(AsyncWebServerRequest *request)
{
    short retry = 0;
    while(retry < 3 && (!dht11_getHumidity())) { retry += 1; };

    if(retry < 3)
        request->send(200, "text/plain", String(dht11_humidity) + "°C");
    else
        request->send(200, "text/plain", "ERROR");
}

// ========== 驱动层 ==========

#define DHT11_DATA_OUT(state) digitalWrite(DHT_PIN, state)
#define DHT11_DATA_IN() digitalRead(DHT_PIN)
#define DHT11_MODE_IN() pinMode(DHT_PIN, INPUT)
#define DHT11_MODE_OUT() pinMode(DHT_PIN, OUTPUT)

/**
 * @brief 复位 DHT11
 * @param 无
 * @retval 无
 */
void dht11_reset(void)
{
    DHT11_MODE_OUT();    // IO 模式设置为输出
    DHT11_DATA_OUT(0);    // 拉低 DQ

    delayNoBlock_ms(20);    // 拉高至少 18ms

    DHT11_DATA_OUT(1);    // 拉高 DQ

    delayNoBlock_us(30);    // 主机拉高 10~35us
}

/**
 * @brief 等待 DHT11 的回应
 * @param 无
 * @retval false 失败 true 正常
 */
bool dht11_check(void)
{
    uint8_t retry = 0;
    uint8_t rval = true;

    DHT11_MODE_IN();    // IO 模式设置为输入

    while (DHT11_DATA_IN() && retry < 100) 
    {
        retry++;
        delayNoBlock_us(83);    // DHT11 会拉低约 83us
    }

    if (retry >= 100)
    {
        rval = false;    // 重试次数过多
    }
    else
    {
        retry = 0;

        while (!DHT11_DATA_IN() && retry < 100)
        {
            retry++;
            delayNoBlock_us(87);    // DHT11 拉低后会再次拉高约 87us
        }
        if (retry >= 100)
        {
            rval = false;    // 重试次数过多
        }
    }

    return rval;
}

/**
 * @brief 初始化 DHT11
 * @param 无
 * @retval false 失败 true 正常
 */
bool dht11_init(void)
{
    dht11_reset();
    return dht11_check();
}

/**
 * @brief 从 DHT11 读取一个位
 * @param 无
 * @retval 读取到的位值: 0 / 1
 */
uint8_t dht11_readBit(void)
{
    uint8_t retry = 0;

    while (DHT11_DATA_IN() && retry < 100)    // 等待变为低电平
    {
        retry++;
        delayNoBlock_us(1);
    }

    retry = 0;
    while (!DHT11_DATA_IN() && retry < 100)    // 等待变高电平
    {
        retry++;
        delayNoBlock_us(1);
    }

    delayNoBlock_us(40);    // 等待 40us
    if (DHT11_DATA_IN())    // 根据引脚状态返回 bit
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 从 DHT11 读取一个字节
 * @param 无
 * @retval 读到的数据
 */
uint8_t dht11_readByte(void)
{
    uint8_t i, data = 0;

    for (i = 0; i < 8; i++)    // 循环读取 8 位数据
    {
        data <<= 1;    // 高位数据先输出, 先左移一位
        data |= dht11_readBit();    // 读取 1bit 数据
    }

    return data;
}

/**
 * @brief 从 DHT11 读取一次数据
 * @param temp 温度值(范围:-20 - 60°)
 * @param humi 湿度值(范围:5% - 95%)
 * @retval false 失败 true 正常
 */
bool dht11_readData(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];

    dht11_reset();

    if(dht11_check())
    {
        for (short i = 0; i < 5; i++) /* 读取 40 位数据 */
        {
            buf[i] = dht11_readByte();
        }

        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            *humi = buf[0];
            *temp = buf[2];

            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}
