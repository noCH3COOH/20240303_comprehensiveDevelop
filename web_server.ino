#include "global.h"

/**
 * @brief 响应网站/setwifi目录的POST请求,收到请求后，运行postCallback_setWIFI回调函数，获取并格式化收到的POST数据
 * @param request 请求
*/
void postCallback_setWIFI(AsyncWebServerRequest *request)
{
    Serial.println("[INFO] 收到设置WIFI按钮");
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
    Serial.println("[INFO] 初始化WEB服务器");
    
    // 响应网站根目录的GET请求,返回文件index.html
    server.serveStatic("/", LittleFS, "/pages/").setDefaultFile("index.html"); 
    server.serveStatic("/icons/", LittleFS, "/icons/");
    
    // POST请求
    server.on("/setwifi", HTTP_POST, postCallback_setWIFI);
    server.on("/setLED", HTTP_POST, postCallback_setLED);

    // GET请求
    server.on("/bomb", HTTP_GET, getCallback_readLED);
    server.on("/wifi", HTTP_GET, getCallback_readWIFI);
    server.on("/ip", HTTP_GET, getCallback_readIP);
    server.on("/APip", HTTP_GET, getCallback_readAPip);

    server.begin();    // 初始化
    Serial.println("[SUCCESS] WEB服务器初始化完成");
}
