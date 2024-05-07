// ==================== includes ====================

#include "game.h"

// ==================== struct ====================

struct gameData {
    bool pressed;
};

// ==================== global variables ====================

struct gameData game_led1, game_led2, game_led3, game_led4;

std::default_random_engine e;

unsigned long game_currentTime = 0;
unsigned long game_previousTime = 0;
const unsigned long game_maxInterval = 5000;

bool victory = false;

// ==================== functions ====================

void game_getKeyState();

void game_led1Pressed();
void game_led2Pressed();
void game_led3Pressed();
void game_led4Pressed();

// ==================== 业务层 ====================

#define set_allLEDState(state) do{ \
    digitalWrite(GAME_LED1_PIN, state); \
    digitalWrite(GAME_LED2_PIN, state); \
    digitalWrite(GAME_LED3_PIN, state); \
    digitalWrite(GAME_LED4_PIN, state); \
}while(0)

#define game_victory() do{ \
    log_now("[SUCCESS] 游戏胜利 :)"); \
    set_allLEDState(GAME_LED_OFF); \
}while(0)

#define game_fail() do{ \
    log_now("[FAILURE] 游戏失败 :("); \
    set_allLEDState(GAME_LED_ON); \
}while(0)

void game_init() 
{
    pinMode(GAME_LED1_PIN, OUTPUT);
    pinMode(GAME_LED2_PIN, OUTPUT);
    pinMode(GAME_LED3_PIN, OUTPUT);
    pinMode(GAME_LED4_PIN, OUTPUT);

    log_now("[INFO] 游戏LED 初始化完成");

    pinMode(GAME_KEY1_PIN, INPUT);
    pinMode(GAME_KEY2_PIN, INPUT);
    pinMode(GAME_KEY3_PIN, INPUT);
    pinMode(GAME_KEY4_PIN, INPUT);

    log_now("[INFO] 游戏按键初始化完成");
}

void game_loop() 
{
    e.seed(time(0));    // 以当前时间为种子

    short led_toPress = ((e() % 4) + 1);    // 生成 1-4 的随机数
    if(led_toPress == 1)
    {
        set_allLEDState(GAME_LED_OFF);
        digitalWrite(GAME_LED1_PIN, GAME_LED_ON);
    }
    else if(led_toPress == 2)
    {
        set_allLEDState(GAME_LED_OFF);
        digitalWrite(GAME_LED2_PIN, GAME_LED_ON);
    }
    else if(led_toPress == 3)
    {
        set_allLEDState(GAME_LED_OFF);
        digitalWrite(GAME_LED3_PIN, GAME_LED_ON);
    }
    else if(led_toPress == 4)
    {
        set_allLEDState(GAME_LED_OFF);
        digitalWrite(GAME_LED4_PIN, GAME_LED_ON);
    }

    log_now("[INFO] 游戏开始");
    game_currentTime = millis();    // 获取当前时间
    
    do{
        game_previousTime = millis();
        game_getKeyState();
    }while(
        (!game_led1.pressed) && 
        (!game_led2.pressed) &&
        (!game_led3.pressed) &&
        (!game_led4.pressed) &&
        (game_previousTime - game_currentTime) < game_maxInterval
    );

    set_allLEDState(GAME_LED_OFF);

    short key_Pressed = 0;
    if(game_led1.pressed)
    {
        key_Pressed = 1;
        game_led1.pressed = false;
    }
    else if(game_led2.pressed)
    {
        key_Pressed = 2;
        game_led2.pressed = false;
    }
    else if(game_led3.pressed)
    {
        key_Pressed = 3;
        game_led3.pressed = false;
    }
    else if(game_led4.pressed)
    {
        key_Pressed = 4;
        game_led4.pressed = false;
    }
    
    if(
        (led_toPress == key_Pressed) && 
        (game_previousTime - game_currentTime) < game_maxInterval
    ){
        game_victory();
    }
    else
    {
        game_fail();
        log_now("[INFO] 正确的按键是：" + String(led_toPress));
    }
    log_now_noNewline("\n");
    log_now("[INFO] 你用时：" + String(game_previousTime - game_currentTime) + "ms");
    log_now("====================");

    log_now("[INFO] 游戏结束，等待一会后重新开始");
}

void game_getKeyState()
{
    if(!digitalRead(GAME_KEY1_PIN))
        game_led1Pressed();
    else if(!digitalRead(GAME_KEY2_PIN))
        game_led2Pressed();
    else if(!digitalRead(GAME_KEY3_PIN))
        game_led3Pressed();
    else if(!digitalRead(GAME_KEY4_PIN))
        game_led4Pressed();
}

void game_led1Pressed()
{
    game_led1.pressed = true;
    log_now("[INFO] 你按下了 1 号按键！");
}

void game_led2Pressed()
{
    game_led2.pressed = true;
    log_now("[INFO] 你按下了 2 号按键！");
}

void game_led3Pressed()
{
    game_led3.pressed = true;
    log_now("[INFO] 你按下了 3 号按键！");
}

void game_led4Pressed()
{
    game_led4.pressed = true;
    log_now("[INFO] 你按下了 4 号按键！");
}
