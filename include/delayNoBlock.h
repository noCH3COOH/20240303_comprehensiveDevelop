#ifndef __DELAYNOBLOCK_H
#define __DELAYNOBLOCK_H

// ==================== includes ====================

#include <Arduino.h>

// ==================== define ====================

#define delayNoBlock_us(us) \
{ \
    unsigned long perviousTime, currentTime = micros(); \
    do { perviousTime = micros(); } while((perviousTime - currentTime) < us); \
}

#define delayNoBlock_ms(ms) \
{ \
    unsigned long perviousTime, currentTime = millis(); \
    do { perviousTime = millis(); } while((perviousTime - currentTime) < ms); \
}

#endif