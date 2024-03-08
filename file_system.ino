#include "global.h"

/**
 * @brief 向文件path中写入字符串
 * @param path 文件的绝对路径
 * @param str 要写入的字符串
*/
bool str2file(String path, String str)
{
    Serial.println("写入文件" + path);
    File wf = LittleFS.open(path, "w");    // 以写入模式打开文件
    if (!wf)
    {    // 如果无法打开文件
        Serial.println("打开文件写入时错误");    // 显示错误信息
        return false;    // 无法打开文件直接返回
    }
    
    wf.print(str);    // 字符串写入文件
    wf.close();    // 关闭文件

    return true;
}

/**
 * @brief 从文件path中读取字符串
 * @param path 文件的绝对路径
 * @return 返回读取的字符串
*/
String file2str(String path)
{
    Serial.println("读取文件");
    File rf = LittleFS.open(path, "r");    // 以读取模式打开文件
    if (!rf)
    {    // 如果无法打开文件
        Serial.println("打开文件读取时错误");    // 显示错误信息
        return "";    // 无法打开文件直接返回
    }
    String str = rf.readString();    // 读取字符串
    rf.close();    // 关闭文件
    return str;
}

/**
 * @brief 解析JSON字符串，从JSON字符串名称得到该值
 * @param str JSON字符串
 * @param Name JSON集合的名称
 * @return 返回值的字符串
*/
String analysis_json(String str, String Name)
{
    DynamicJsonDocument doc(str.length() * 2);    // 定义一个JSON对象
    deserializeJson(doc, str);     // 反序列数据
    String value = doc[Name].as<String>();    // 从Name中读取对应的值
    return value;
}

/**
 * @brief 初始化文件系统
*/
void LittleFS_begin()
{
    Serial.println();
    Serial.println("初始化文件系统");
    if (!LittleFS.begin(true))
    {
        Serial.println("文件系统初始化错误");
        return;
    }
}

/**
 * @brief 更新配置文件
*/
void update_config()
{
    Serial.println("更新配置文件");
    
    StaticJsonDocument<200> config;
    String str_config;
    short retry = 0;
        
    // 写成一个JSON格式
    config["wifiname"] = global_config.wifiname.c_str();
    config["wifipassword"] = global_config.wifipassword.c_str();
    config["ip"] = global_config.ip.c_str();
    config["AP_ip"] = global_config.AP_ip.c_str();
    config["AP_ssid"] = global_config.AP_ssid.c_str();
    config["AP_password"] = global_config.AP_password.c_str();
    config["AP_url"] = global_config.AP_url.c_str();
        
    serializeJson(config, str_config);    // 生成JOSN的字符串
    while( (retry < 3) && (!str2file("/config.json", str_config)) )
    {
        retry += 1;
        if(retry < 3)
            Serial.printf("配置文件更新失败，重试 %d 次", retry);
        else
            Serial.println("配置文件更新全部失败，请重置系统");
    }
}
