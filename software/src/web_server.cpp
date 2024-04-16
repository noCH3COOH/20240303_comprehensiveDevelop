// =========================== includes ===========================

#include "web_server.h"

// =========================== global variables ===========================

static AsyncWebServer server(80);    // 创建一个服务器对象，WEB服务器端口:80

// =========================== functions ===========================

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
