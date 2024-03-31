#ifndef __log_H
#define __log_H

// ==================== includes ====================

#include <Arduino.h>

// ==================== functions ====================

void log_init();
void log_now(String str);
void log_now(const char *str);

void log_now_noNewline(String str);
void log_now_noNewline(const char *str);

#endif    // __log_H
