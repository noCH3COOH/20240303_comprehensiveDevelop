// ===================== includes ====================
#include "xpt2046.h"

// ==================== global variables ====================

struct XPT2046_TOUCH_t xpt2046_touch;
enum XPT2046_ROTATION_t xpt2046_rotation = XPT_ROTATE_0;

// ==================== functions ====================

/**
 * @brief 初始化
*/
void XPT2046_touchInit(void)
{
    // 初始化GPIO口
    pinMode(IRQ_PIN, INPUT);
    pinMode(MISO_PIN, INPUT);
    pinMode(MOSI_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);

    digitalWrite(IRQ_PIN, HIGH);
    digitalWrite(MISO_PIN, HIGH);
    digitalWrite(MOSI_PIN, HIGH);
    digitalWrite(CS_PIN, HIGH);
    digitalWrite(CLK_PIN, HIGH);
}

void XPT2046_setRotation(XPT2046_ROTATION_t rotation)
{
    xpt2046_rotation = rotation;
}

/**
 * @brief SPI底层写一个字节
 * @param cmd 要写入的数据
*/
void XPT2046_SPI_writeOneByte(uint8_t cmd)
{
    for(short i=0;i<8;i++)
    {
        digitalWrite(CLK_PIN, LOW);    // 低电平写

        if(cmd & 0x80) { digitalWrite(MOSI_PIN, HIGH); }
        else { digitalWrite(MOSI_PIN, LOW); }

        cmd<<=1;
        digitalWrite(CLK_PIN, HIGH);   // 高电平读
    }
}

/**
 * @brief 读取数据，2个字节
 * @param cmd 要读取的数据
 * @return 读取到的数据
 * @note 读取16位数据，最低4位数据无效，有效数据是高12位
*/
uint16_t XPT2046_readData(uint8_t cmd)
{
    uint16_t data;
    
    digitalWrite(CS_PIN, LOW);    // 选中XPT2046
    digitalWrite(MOSI_PIN, LOW);  // 通知XPT2046,主机需要数据
    digitalWrite(CLK_PIN, LOW);
    XPT2046_SPI_writeOneByte(cmd);
    
    delayNoBlock_us(8);    // 0.008ms ,等待XPT2046转换完成。

    // 消除忙信号
    digitalWrite(CLK_PIN, LOW);
    delayNoBlock_us(1);
    digitalWrite(CLK_PIN, HIGH);
    
    // 连续读取16位的数据
    for(short i=0;i<16;i++)
    {
        digitalWrite(CLK_PIN, LOW);    // 通知XPT2046,主机需要数据
        digitalWrite(CLK_PIN, HIGH);

        data = data << 1;

        if(digitalRead(MISO_PIN)) { data |= 0x01; };
    }

    data = data >> 4;    // 丢弃最低4位
    
    digitalWrite(CS_PIN, HIGH);    // 取消选中
    return data;
}

/**
 * @brief 读取触摸屏的坐标
 * @return 读取到坐标返回true,否则返回false
 * @note 读取到的坐标存放在xpt2046_touch结构体中
*/
bool XPT2046_readXY(void)
{
    if(LOW == digitalRead(IRQ_PIN)) //判断触摸屏是否按下
    {
        /*1. 得到物理坐标*/
        xpt2046_touch.x0 = XPT2046_readData(CMD_READ_X);
        xpt2046_touch.y0 = XPT2046_readData(CMD_READ_Y);

        uint16_t x = LCD_WIDTH - ((float)xpt2046_touch.x0 - 155) / ((float)3676 / LCD_WIDTH);
        uint16_t y = LCD_HEIGHT - ((float)xpt2046_touch.y0 - 168) / ((float)3766 / LCD_HEIGHT);
      
        /*2. 得到像素坐标*/
        if(xpt2046_rotation == XPT_ROTATE_0)
        {
            xpt2046_touch.x = LCD_WIDTH - x;
            xpt2046_touch.y = y;
        }
        else if(xpt2046_rotation == XPT_ROTATE_90)
        {
            xpt2046_touch.x = y;
            xpt2046_touch.y = x;
        }
        else if(xpt2046_rotation == XPT_ROTATE_180)
        {
            xpt2046_touch.x = x;
            xpt2046_touch.y = LCD_HEIGHT - y;
        }
        else if(xpt2046_rotation == XPT_ROTATE_270)
        {
            xpt2046_touch.x = LCD_WIDTH - y;
            xpt2046_touch.y = LCD_WIDTH - x;
        }

        // log_now("[INFO] 像素坐标: (" + String(xpt2046_touch.x) + ", " + String(xpt2046_touch.y) + ")");

        digitalWrite(IRQ_PIN, HIGH);    // 释放触摸屏(必须释放,否则下次无法读取坐标)
        
        return true;
    }
    return false;
}
/*
XPT2046的命令:

10010000  :测试Y的坐标 0x90
11010000  :测试X的坐标 0xD0

返回值:  0表示没有读取到坐标,1表示读取到当前坐标

//1. 得到左上角和右下角的坐标XY极限值
  x=3831,y=3934
  x=155,y=168

//2. 转换坐标值
  x坐标:3831 - 155 ==>  3676 - 0
  y坐标:3934 - 168 ==>  3766 - 0

//3. 计算斜率
  x坐标的斜率: 3676/320=11.4875
  y坐标的斜率: 3766/480=7.84583

//4. 得到实际的像素坐标
  x坐标:  320-(模拟量-155)/11.4875
  y坐标:  480-(模拟量-168)/7.84583
*/

/**
 * @brief 获取触摸屏的坐标
*/
XPT2046_retval_t XPT2046_getTouch(void)
{
    if(XPT2046_readXY())
    {
        return {xpt2046_touch, true};
    }
    else
    {
        xpt2046_touch.x = 0;
        xpt2046_touch.y = 0;
        return {xpt2046_touch, false};
    }
}
