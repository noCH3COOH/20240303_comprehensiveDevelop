// ===================== includes ====================

#include "xpt2046.h"

// ==================== defines ====================

#define MOSI_PIN DIN_PIN
#define MISO_PIN DO_PIN

#define CMD_READ_Y 0x90
#define CMD_READ_X 0xD0

// 方便更换不同的延迟函数适配不同的平台
#define XPT_delay_ms(ms) do{ \
    unsigned long perviousTime, currentTime = millis(); \
    do { perviousTime = millis(); } while((perviousTime - currentTime) < ms); \
} while(0)

#define XPT_delay_us(us) do{ \
    unsigned long perviousTime, currentTime = micros(); \
    do { perviousTime = micros(); } while((perviousTime - currentTime) < us); \
} while(0)

// ==================== global variables ====================

XPT2046_TOUCH_t XPT_touch;
XPT2046_ROTATION_t XPT_rotation = XPT_ROTATE_0;

// ==================== functions ====================

/**
 * @brief 初始化
*/
void XPT2046_touchInit(void)
{
    // 初始化GPIO口
    XPT_PIN_INIT();

    XPT_IRQ_WRITE(XPT_PIN_HIGH);
    XPT_CS_WRITE(XPT_PIN_HIGH);
    XPT_CLK_WRITE(XPT_PIN_HIGH);
    XPT_MOSI_WRITE(XPT_PIN_HIGH);
    XPT_MOSI_WRITE(XPT_PIN_HIGH);
}

void XPT2046_setRotation(XPT2046_ROTATION_t rotation)
{
    XPT_rotation = rotation;
}

/**
 * @brief SPI底层写一个字节
 * @param cmd 要写入的数据
*/
void XPT2046_SPI_writeOneByte(uint8_t cmd)
{
    for(short i=0;i<8;i++)
    {
        XPT_CLK_WRITE(XPT_PIN_LOW);    // 低电平写

        if(cmd & 0x80) { XPT_MOSI_WRITE(XPT_PIN_HIGH); }
        else { XPT_MOSI_WRITE(XPT_PIN_LOW); }

        cmd<<=1;
        XPT_CLK_WRITE(XPT_PIN_HIGH);   // 高电平读
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
    
    XPT_CS_WRITE(XPT_PIN_LOW);    // 选中XPT2046
    XPT_MOSI_WRITE(XPT_PIN_LOW);  // 通知XPT2046,主机需要数据
    XPT_CLK_WRITE(XPT_PIN_LOW);
    XPT2046_SPI_writeOneByte(cmd);
    
    XPT_delay_us(8);    // 0.008ms ,等待XPT2046转换完成。

    // 消除忙信号
    XPT_CLK_WRITE(XPT_PIN_LOW);
    XPT_delay_us(1);
    XPT_CLK_WRITE(XPT_PIN_HIGH);
    
    // 连续读取16位的数据
    for(short i=0;i<16;i++)
    {
        XPT_CLK_WRITE(XPT_PIN_LOW);    // 通知XPT2046,主机需要数据
        XPT_CLK_WRITE(XPT_PIN_HIGH);

        data = data << 1;

        if(XPT_MISO_READ()) { data |= 0x01; };
    }

    data = data >> 4;    // 丢弃最低4位
    
    XPT_CS_WRITE(XPT_PIN_HIGH);    // 取消选中
    return data;
}

/**
 * @brief 读取触摸屏的坐标
 * @return 读取到坐标返回`XPT_TRUE`,否则返回`XPT_FALSE`
 * @note 读取到的坐标存放在`XPT_touch`结构体中
*/
XPT_bool_t XPT2046_readXY(void)
{
    if(XPT_IRQ_MODE == XPT_IRQ_READ()) //判断触摸屏是否按下
    {
        /*1. 得到物理坐标*/
        XPT_touch.x0 = XPT2046_readData(CMD_READ_X);
        XPT_touch.y0 = XPT2046_readData(CMD_READ_Y);

        uint16_t x = LCD_WIDTH - ((float)XPT_touch.x0 - 155) / ((float)3676 / LCD_WIDTH);
        uint16_t y = LCD_HEIGHT - ((float)XPT_touch.y0 - 168) / ((float)3766 / LCD_HEIGHT);
      
        /*2. 得到像素坐标*/
        if(XPT_rotation == XPT_ROTATE_0)
        {
            XPT_touch.x = LCD_WIDTH - x;
            XPT_touch.y = y;
        }
        else if(XPT_rotation == XPT_ROTATE_90)
        {
            XPT_touch.x = y;
            XPT_touch.y = x;
        }
        else if(XPT_rotation == XPT_ROTATE_180)
        {
            XPT_touch.x = x;
            XPT_touch.y = LCD_HEIGHT - y;
        }
        else if(XPT_rotation == XPT_ROTATE_270)
        {
            XPT_touch.x = LCD_WIDTH - y;
            XPT_touch.y = LCD_WIDTH - x;
        }

        XPT_IRQ_WRITE(XPT_PIN_HIGH);    // 释放触摸屏(必须释放,否则下次无法读取坐标)

        return XPT_TRUE;
    }
    return XPT_FALSE;
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
    XPT2046_retval_t retval;

    if(XPT2046_readXY())
    {
        retval.point = XPT_touch;

        retval.ret = XPT_TRUE;
        return retval;
    }
    else
    {
        XPT_touch.x = 0;
        XPT_touch.y = 0;
        retval.point = XPT_touch;

        retval.ret = XPT_FALSE;
        return retval;
    }
}
