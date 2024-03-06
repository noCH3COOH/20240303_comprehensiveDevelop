#include "global.h"

DNSServer dnsserver;

/**
 * @brief 连接WIFI
 * @param ssid WIFI名称
 * @param password WIFI密码
 */
void connect_WIFI(String ssid, String password)
{
    WiFi.begin(ssid.c_str(), password.c_str()); // 连接WIFI
    Serial.print("连接WIFI");
    
    // 循环，10秒后连接不上跳出循环
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
        i++;
        if (i > 20)
        {
            Serial.println();
            Serial.println("WIFI连接失败");
            return;
        }
    }
    
    Serial.println();
    IPAddress local_IP = WiFi.localIP();
    Serial.print("WIFI连接成功，本地IP地址:"); // 连接成功提示
    Serial.println(local_IP);
}

/**
 * @brief 连接WIFI
*/
void connect_NET()
{
    const byte DNS_PORT = 53;                         // DNS端口
    const String url = "ESPAP.com";                   // 域名
    const char *APSsid = "esp32_AP";                  // AP SSID
    const char *APPassword = "12345678";              // AP wifi密码
    IPAddress APIp(10, 0, 10, 1);                     // AP IP
    IPAddress APGateway(10, 0, 10, 1);                // AP网关
    IPAddress APSubnetMask(255, 255, 255, 0);         // AP子网掩码

    wifi_connect();                                   // 连接WIFI

    WiFi.mode(WIFI_AP_STA);                           // 打开AP和STA共存模式
    WiFi.softAPConfig(APIp, APGateway, APSubnetMask); // 设置AP的IP地址，网关和子网掩码
    WiFi.softAP(APSsid, APPassword, 6);               // 设置AP模式的登陆名和密码

    dnsserver.start(DNS_PORT, url, APIp);             // 设置DNS的端口、网址、和IP

    Serial.print("AP模式IP地址为:");
    Serial.println(WiFi.softAPIP());
}

/**
 * @brief DNS服务请求处理
*/
void DNS_request_loop()
{
    dnsserver.processNextRequest();
}