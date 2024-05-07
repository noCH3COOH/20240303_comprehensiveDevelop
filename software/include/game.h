#ifndef __GAME_H__
#define __GAME_H__

#include <Arduino.h>
#include "delayNoBlock.h"
#include "log.h"
#include <iostream>
#include <ctime>
#include <random>

#define GAME_LED1_PIN 39
#define GAME_LED2_PIN 7
#define GAME_LED3_PIN 16
#define GAME_LED4_PIN 20

#define GAME_LED_ON 0
#define GAME_LED_OFF 1

#define GAME_KEY1_PIN 3
#define GAME_KEY2_PIN 9
#define GAME_KEY3_PIN 14
#define GAME_KEY4_PIN 48

void game_init();
void game_loop();

#endif
