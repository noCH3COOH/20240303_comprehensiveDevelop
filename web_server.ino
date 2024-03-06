#include "global.h"

/**
 * @brief 响应网站/setwifi目录的POST请求,收到请求后，运行get_WIFI_set_CALLback回调函数，获取并格式化收到的POST数据
 * @param request 请求
*/
void get_WIFI_set_CALLback(AsyncWebServerRequest *request)
{
    Serial.println("收到设置WIFI按钮");
    if (request->hasParam("wifiname", true))
    {
        AsyncWebParameter *wifiname = request->getParam("wifiname", true);    // 获取POST数据
        AsyncWebParameter *wifipassword = request->getParam("wifipassword", true);    // 获取POST数据
        String wn = wifiname->name().c_str();
        String wnv = wifiname->value().c_str();
        String wp = wifipassword->name().c_str();
        String wpv = wifipassword->value().c_str();
        // 把SSID和password写成一个JSON格式
        StaticJsonDocument<200> wifi_json;    // 创建一个JSON对象,wifi_json
        wifi_json[wn] = wnv;    // 写入一个建和值
        wifi_json[wp] = wpv;    // 写入一个键和值
        String wifi_json_str;    // 定义一个字符串变量
        serializeJson(wifi_json, wifi_json_str);    // 生成JOSN的字符串
        str_write("/WIFIConfig.conf", wifi_json_str);    // 字符串写入
    }
}

/**
 * @brief 从/WIFIConfig.conf文件中读取数据并连接WIFI
*/
void wifi_connect()
{
    Serial.println("在conf文件中读取数据并连接WIFI");
    String str = str_read("/WIFIConfig.conf");    // 读取文件内容
    String wifiname = analysis_json(str, "wifiname");    // 解析WIFI名称
    String wifipassword = analysis_json(str, "wifipassword");    // 解析WIFI密码
    connect_WIFI(wifiname, wifipassword);    // 连接WIFI
}

/**
 * @brief 初始化WEB服务器
*/
void web_server()
{
    Serial.println("初始化WEB服务器");
<<<<<<< HEAD
    
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");    // 响应网站根目录的GET请求,返回文件index.html
    
=======
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");    // 响应网站根目录的GET请求,返回文件index.html
>>>>>>> da937894b5889d83759150e4d349ae478b550194
    server.on("/setwifi", HTTP_POST, get_WIFI_set_CALLback);    // 响应设置WIFI按钮的请求
    server.on("/GPIO2", HTTP_GET, GPIO_button);    // 响应改变引脚按钮的请求
    server.begin();    // 初始化
}
