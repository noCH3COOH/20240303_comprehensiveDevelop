// =========================== includes ===========================

#include "web_server.h"

// =========================== global variables ===========================

static AsyncWebServer server(80);    // 创建一个服务器对象，WEB服务器端口:80
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
    log_now("[INFO] 连接WIFI: " + String(ssid.c_str()));

    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        log_now_noNewline(".");
        delayNoBlock_ms(1000);
        i++;
        if (i > 5)
        {
            log_now("");
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
 * @brief 初始化WEB服务器
*/
void web_server()
{
    log_now("[INFO] 初始化WEB服务器");
    
    // 响应网站根目录的GET请求,返回文件index.html
    server.serveStatic("/", LittleFS, "/pages/").setDefaultFile("index.html"); 
    server.serveStatic("/icons/", LittleFS, "/icons/");
    
    // POST请求
    server.on("/setwifi", HTTP_POST, postCallback_setWIFI);
    server.on("/setLED", HTTP_POST, postCallback_setLED);

    // GET请求
    server.on("/temp", HTTP_GET, getCallback_readTemp);
    server.on("/wet", HTTP_GET, getCallback_readWet);
    server.on("/bomb", HTTP_GET, getCallback_readLED);
    server.on("/wifi", HTTP_GET, getCallback_readWIFI);
    server.on("/ip", HTTP_GET, getCallback_readIP);
    server.on("/APip", HTTP_GET, getCallback_readAPip);

    server.begin();    // 初始化
    log_now("[SUCCESS] WEB服务器初始化完成");
}

// =========================== 网页回调函数 ===========================

/**
 * @brief 响应网站/setwifi目录的POST请求,收到请求后，运行postCallback_setWIFI回调函数，获取并格式化收到的POST数据
 * @param request 请求
*/
void postCallback_setWIFI(AsyncWebServerRequest *request)
{
    log_now("[INFO] 收到设置WIFI按钮");
    if (request->hasParam("wifiname", true))
    {
        AsyncWebParameter *wifiname = request->getParam("wifiname", true);    // 获取POST数据
        AsyncWebParameter *wifipassword = request->getParam("wifipassword", true);    // 获取POST数据
        
        global_config.wifiname = String(wifiname->value().c_str());    // 设置WIFI名称
        global_config.wifipassword = String(wifipassword->value().c_str());    // 设置WIFI密码

        update_config();    // 更新配置文件
    }
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
