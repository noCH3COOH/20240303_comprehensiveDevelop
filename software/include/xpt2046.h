#ifndef XPT2046_TOUCH_H
#define XPT2046_TOUCH_H

// ==================== includes ====================

#include <Arduino.h>
#include "delayNoBlock.h"
#include "log.h"

// ==================== defines ====================

#define IRQ_PIN 5
#define DO_PIN 4
#define DIN_PIN 6
#define CS_PIN 15
#define CLK_PIN 17

#define MOSI_PIN DIN_PIN
#define MISO_PIN DO_PIN

#define CMD_READ_Y 0x90
#define CMD_READ_X 0xD0

#define LCD_WIDTH 320
#define LCD_HEIGHT 480

// ==================== structs ====================

enum XPT2046_ROTATION_t
{
    XPT_ROTATE_0 = 0,
    XPT_ROTATE_90 = 1,
    XPT_ROTATE_180 = 2,
    XPT_ROTATE_270 = 3
};

struct XPT2046_TOUCH_t
{
    uint16_t x0; //物理坐标x
    uint16_t y0; //物理坐标y
    uint16_t x;  //像素坐标x
    uint16_t y;  //像素坐标y
};

struct XPT2046_retval_t
{
    XPT2046_TOUCH_t point;
    bool ret;
};

// ==================== functions ====================

void XPT2046_touchInit(void);
void XPT2046_setRotation(XPT2046_ROTATION_t rotation);
XPT2046_retval_t XPT2046_getTouch(void);

#endif   // XPT2046_TOUCH_H
