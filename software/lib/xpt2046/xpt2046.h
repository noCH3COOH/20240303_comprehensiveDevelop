#ifndef XPT2046_TOUCH_H
#define XPT2046_TOUCH_H

// ==================== includes ====================

#include <Arduino.h>

// ==================== defines ====================

// 以下可设置XPT2046的引脚定义
#define IRQ_PIN 5
#define DO_PIN 4    // 触摸屏上是什么就是什么，不必自行更改
#define DIN_PIN 6
#define CS_PIN 15
#define CLK_PIN 17

// 以下可设置LCD的宽高
#define LCD_WIDTH 320
#define LCD_HEIGHT 480

// 以下可设置XPT2046的引脚高低电平定义
#define XPT_PIN_HIGH HIGH
#define XPT_PIN_LOW LOW

// 以下可设置XPT2046的IRQ引脚中断触发方式
/**
 * @note 有些XPT2046芯片的IRQ引脚是高电平触发，有些是低电平触发
 * @note 如果你发现触摸屏读到的坐标一直是最大值，且不会变化，那么请尝试更改此宏定义
*/
// #define XPT_IRQ_MODE HIGH
#ifndef XPT_IRQ_MODE
#define XPT_IRQ_MODE LOW
#endif

// 以下可设置XPT2046的引脚初始化宏定义
#define XPT_PIN_INIT() do{ \
    pinMode(IRQ_PIN, INPUT); \
    pinMode(DO_PIN, INPUT); \
    pinMode(DIN_PIN, OUTPUT); \
    pinMode(CS_PIN, OUTPUT); \
    pinMode(CLK_PIN, OUTPUT); \
} while(0)

// 以下可设置XPT2046的引脚操作宏定义
#define XPT_IRQ_WRITE(state) digitalWrite(IRQ_PIN, state)
#define XPT_IRQ_READ() digitalRead(IRQ_PIN)
#define XPT_CS_WRITE(state) digitalWrite(CS_PIN, state)
#define XPT_MISO_READ() digitalRead(MISO_PIN)
#define XPT_CS_WRITE(state) digitalWrite(CS_PIN, state)
#define XPT_CLK_WRITE(state) digitalWrite(CLK_PIN, state)
#define XPT_MOSI_WRITE(state) digitalWrite(MOSI_PIN, state)

// ==================== enums and structs ====================

enum XPT_bool_enum_t
{
    XPT_FALSE = 0,
    XPT_TRUE = 1
};
typedef enum XPT_bool_enum_t XPT_bool_t;

enum XPT2046_ROTATION_enum_t
{
    XPT_ROTATE_0 = 0,
    XPT_ROTATE_90 = 1,
    XPT_ROTATE_180 = 2,
    XPT_ROTATE_270 = 3
};
typedef enum XPT2046_ROTATION_enum_t XPT2046_ROTATION_t;

struct XPT2046_TOUCH_struct_t
{
    uint16_t x0; //物理坐标x
    uint16_t y0; //物理坐标y
    uint16_t x;  //像素坐标x
    uint16_t y;  //像素坐标y
};
typedef struct XPT2046_TOUCH_struct_t XPT2046_TOUCH_t;

struct XPT2046_retval_struct_t
{
    XPT2046_TOUCH_t point;
    XPT_bool_t ret;
};
typedef struct XPT2046_retval_struct_t XPT2046_retval_t;

// ==================== functions ====================

void XPT2046_touchInit(void);
void XPT2046_setRotation(XPT2046_ROTATION_t rotation);
XPT2046_retval_t XPT2046_getTouch(void);

#endif   // XPT2046_TOUCH_H
