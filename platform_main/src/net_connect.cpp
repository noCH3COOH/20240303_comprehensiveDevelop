// =========================== includes ===========================

#include "net_connect.h"

// =========================== global variables ===========================

AsyncWebServer server(80);    // 创建一个服务器对象，WEB服务器端口:80
DNSServer dnsserver;    // 创建一个DNS服务器对象

// =========================== functions ===========================

/**
 * @brief 连接WIFI
 * @param ssid WIFI名称
 * @param password WIFI密码
 */
void connect_WIFI(String ssid, String password)
{
    WiFi.begin(ssid.c_str(), password.c_str());    // 连接WIFI
    log_now("[INFO] 连接WIFI");
    
    // 循环，10秒后连接不上跳出循环
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        log_now_noNewline(".");
        log_now("");
        delayNoBlock_ms(500);
        i++;
        if (i > 20)
        {
            log_now("[ERROR] WIFI连接失败");
            return;
        }
    }
    
    log_now_noNewline("[SUCCESS] WIFI连接成功:");    // 连接成功提示
    log_now(ssid.c_str());
    log_now_noNewline("[INFO] 本地IP地址:");
    log_now(WiFi.localIP().toString());
}

/**
 * @brief 连接WIFI
*/
void connect_NET()
{
    IPAddress AP_ip(10, 0, 10, 1);    // AP IP
    IPAddress AP_gateway(10, 0, 10, 1);    // AP网关
    IPAddress AP_subnetMask(255, 255, 255, 0);    // AP子网掩码
    const byte DNS_port = 53;    // DNS端口
    const char *AP_ssid = global_config.AP_ssid.c_str();    // AP SSID
    const char *AP_password = global_config.AP_password.c_str();    // AP wifi密码
    const String AP_url = global_config.AP_url.c_str();    // 域名
    String str = file2str("/config.json");    // 读取文件内容
    String wifiname = analysis_json(str, "wifiname");    // 解析WIFI名称
    String wifipassword = analysis_json(str, "wifipassword");    // 解析WIFI密码

    connect_WIFI(wifiname, wifipassword);    // 连接WIFI

    WiFi.mode(WIFI_AP_STA);    // 打开AP和STA共存模式
    WiFi.softAPConfig(AP_ip, AP_gateway, AP_subnetMask);    // 设置AP的IP地址，网关和子网掩码
    WiFi.softAP(AP_ssid, AP_password, 6);    // 设置AP模式的登陆名和密码

    dnsserver.start(DNS_port, AP_url, AP_ip);    // 设置DNS的端口、网址、和IP
    
    log_now("[INFO] AP模式IP地址为:" + WiFi.softAPIP().toString());

    global_config.wifiname = wifiname;    // 设置WIFI名称
    global_config.wifipassword = wifipassword;    // 设置WIFI密码
    global_config.ip = WiFi.localIP().toString();    // 获取WIFI模式IP地址
    global_config.AP_ip = WiFi.softAPIP().toString();    // 获取AP模式IP地址 

    update_config();    // 更新配置文件
}

/**
 * @brief DNS服务请求处理
*/
void DNS_request_loop()
{
    dnsserver.processNextRequest();
}

/**
 * @brief 返回网络参数
*/
void getCallback_readWIFI(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", global_config.wifiname);
}

/**
 * @brief 返回网络参数
*/
void getCallback_readIP(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", global_config.ip);
}

/**
 * @brief 返回网络参数
*/
void getCallback_readAPip(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", global_config.AP_ip);
}
