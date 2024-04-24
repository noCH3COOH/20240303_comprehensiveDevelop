#ifndef __DELAYNOBLOCK_H
#define __DELAYNOBLOCK_H

// ==================== includes ====================

#include <Arduino.h>

// ==================== define ====================

#define delayNoBlock_us(us) do{ \
    unsigned long perviousTime, currentTime = micros(); \
    do { perviousTime = micros(); } while((perviousTime - currentTime) < us); \
} while(0)

#define delayNoBlock_ms(ms) do{ \
    unsigned long perviousTime, currentTime = millis(); \
    do { perviousTime = millis(); } while((perviousTime - currentTime) < ms); \
} while(0)

#endif