#include "global.h"

/**
 * @brief 向文件path中写入字符串
 * @param path 文件的绝对路径
 * @param str 要写入的字符串
*/
void str_write(String path, String str)
{
    Serial.println("写入文件");
    File wf = LittleFS.open(path, "w");    // 以写入模式打开文件
    if (!wf)
    {    // 如果无法打开文件
        Serial.println("打开文件写入时错误");    // 显示错误信息
        return;    // 无法打开文件直接返回
    }
    wf.print(str);    // 字符串写入文件
    wf.close();    // 关闭文件
    File rf = LittleFS.open(path, "r");    // 以读取模式打开文件
    Serial.print("FILE:");
    Serial.println(rf.readString());    // 读取文件
    rf.close();    // 关闭文件
}

/**
 * @brief 从文件path中读取字符串
 * @param path 文件的绝对路径
 * @return 返回读取的字符串
*/
String str_read(String path)
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
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
}
