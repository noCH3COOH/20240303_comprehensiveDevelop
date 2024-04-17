// =========================== includes ===========================

#include "web_server.h"

// =========================== global variables ===========================

static AsyncWebServer server(80);    // 创建一个服务器对象，WEB服务器端口:80
DNSServer dnsserver;    // 创建一个DNS服务器对象

IPAddress AP_ip(10, 0, 10, 1);    // AP IP
IPAddress AP_gateway(10, 0, 10, 1);    // AP网关
IPAddress AP_subnetMask(255, 255, 255, 0);    // AP子网掩码
const byte DNS_port = 53;    // DNS端口

String scanNetworksID = "";
String netSet_page = "";

bool isAP = false;    // 是否为AP模式

// =========================== functions ===========================

/**
 * @brief 初始化WEB服务器
*/
void init_webServer()
{
    server.reset();    // 重置服务器

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

/**
 * @brief 连接WIFI
*/
void init_network()
{
    String str = file2str("/config.json");    // 读取文件内容
    String wifiname = analysis_json(str, "wifiname");    // 解析WIFI名称
    String wifipassword = analysis_json(str, "wifipassword");    // 解析WIFI密码

    connect_WIFI(wifiname, wifipassword);    // 连接WIFI

    update_config();    // 更新配置文件
}

/**
 * @brief 连接WIFI
 * @param ssid WIFI名称
 * @param password WIFI密码
 */
void connect_WIFI(String ssid, String password)
{
    WiFi.mode(WIFI_STA);    // 设置WIFI模式为STA

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

    global_config.wifiname = ssid;    // 设置WIFI名称
    global_config.wifipassword = password;    // 设置WIFI密码
    global_config.ip = WiFi.localIP().toString();    // 获取WIFI模式IP地址
}

/**
 * @brief 设置AP配网模式
*/
String set_net_AP()
{
    isAP = true;    // 设置为AP模式

    if(WiFi.status() == WL_CONNECTED)    // 如果已经连接WIFI
    {
        WiFi.disconnect();    // 断开WIFI连接
        delayNoBlock_ms(1000);
    }

    server.reset();
    
    log_now( scan_wifi() ? "[INFO] 附近扫描到wifi" : "[INFO] 附近未扫描到wifi" );
    netSet_page = LittleFS.open("/pages/AP.html", "r").readString();    // 读取文件内容
    netSet_page.replace("<datalist id = \"data-list\"></datalist>", scanNetworksID);    // 替换字符串

    WiFi.mode(WIFI_AP);    // 设置WIFI模式为AP
    WiFi.softAPConfig(AP_ip, AP_gateway, AP_subnetMask);    // 设置AP IP地址
    WiFi.softAP(global_config.AP_ssid.c_str());    // 设置AP SSID

    log_now("[INFO] 设置AP配网模式");
    log_now("[INFO] AP SSID: " + global_config.AP_ssid);
    log_now("[INFO] AP IP: " + AP_ip.toString());

    dnsserver.start(DNS_port, "*", AP_ip);    // 启动DNS服务
    log_now("[SUCCESS] AP配网模式设置成功");

    server.on("/", HTTP_GET, callback_APnetSet);
    server.on("/setWifi_AP", HTTP_POST, postCallback_setWIFI_AP);

    server.begin();

    global_config.AP_ip = AP_ip.toString();

    return AP_ip.toString();
}

/**
 * @brief 扫描WIFI供配网界面使用
*/
bool scan_wifi()
{
    // 扫描附近WiFi
    int n = WiFi.scanNetworks();
    if (n == 0)
    {
        Serial.println("no networks found");
        scanNetworksID += "<option>no networks found</option>";
        return false;
    }
    else
    {
        scanNetworksID += "<datalist id = \"data-list\">\n";
        for (int i = 0; i < n; ++i)
        {
            scanNetworksID += "<option>" + WiFi.SSID(i) + "</option>\n";
            delayNoBlock_ms(10);
        }
        scanNetworksID += "</datalist>";
        return true;
    }
}

/**
 * @brief DNS服务请求处理
*/
void DNS_request_loop()
{
    // dnsserver.processNextRequest();
}

// =========================== 网页回调函数 ===========================

/**
 * @brief 强制门户设置IP主页
*/
void callback_APnetSet(AsyncWebServerRequest *request)
{
    request->send(200, "html", netSet_page.c_str());
}

/**
 * @brief 强制门户设置需要连接的WIFI
*/
void postCallback_setWIFI_AP(AsyncWebServerRequest *request)
{
    log_now("[INFO] 收到设置WIFI按钮");

    if (request->hasParam("auth_user", true) && request->hasParam("auth_pass", true))
    {
        request->send(200, "text/plain", "OK");

        AsyncWebParameter *auth_user = request->getParam("auth_user", true);    // 获取POST数据
        AsyncWebParameter *auth_pass = request->getParam("auth_pass", true);    // 获取POST数据

        global_config.wifiname = String(auth_user->value().c_str());    // 设置WIFI名称
        global_config.wifipassword = String(auth_pass->value().c_str());    // 设置WIFI密码

        update_config();    // 更新配置文件

        log_now("[INFO] 更新连接WIFI：" + global_config.wifiname);
    }

    connect_WIFI(global_config.wifiname, global_config.wifipassword);    // 连接WIFI
    init_webServer();    // 初始化WEB服务器
    
    isAP = false;    // 设置为非AP模式
}

/**
 * @brief 响应网站/setwifi目录的POST请求,收到请求后，运行postCallback_setWIFI回调函数，获取并格式化收到的POST数据
 * @param request 请求
*/
void postCallback_setWIFI(AsyncWebServerRequest *request)
{
    log_now("[INFO] 收到设置WIFI按钮");
    if (request->hasParam("wifiname", true))
    {
        request->send(200, "text/plain", "OK");

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
