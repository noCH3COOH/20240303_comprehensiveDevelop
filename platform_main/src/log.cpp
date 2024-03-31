// =========================== includes ===========================

#include "log.h"

// =========================== functions ===========================

/**
 * @brief 日志初始化
*/
void log_init()
{
    Serial.begin(115200);
}

/**
 * @brief 立即输出日志
*/
void log_now(String str)
{
    Serial.println(str.c_str());
}

/**
 * @brief 立即输出日志
*/
void log_now(const char *str)
{
    Serial.println(str);
}

/**
 * @brief 立即输出日志
*/
void log_now_noNewline(String str)
{
    Serial.print(str.c_str());
}

/**
 * @brief 立即输出日志
*/

void log_now_noNewline(const char *str)
{
    Serial.print(str);
}
