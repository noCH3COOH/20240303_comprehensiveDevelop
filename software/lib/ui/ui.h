// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_TabView1;
extern lv_obj_t * ui_paraPage;
extern lv_obj_t * ui_tempPanel;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_tempLabel;
extern lv_obj_t * ui_brightPanel;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_brightLabel;
extern lv_obj_t * ui_wetPanel;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_wetLabel;
extern lv_obj_t * ui_bombPanel;
extern lv_obj_t * ui_Image5;
extern lv_obj_t * ui_bombLabel;
extern lv_obj_t * ui_fanPanel;
extern lv_obj_t * ui_Image7;
extern lv_obj_t * ui_fanLabel;
extern lv_obj_t * ui_wifiPanel;
extern lv_obj_t * ui_Image8;
extern lv_obj_t * ui_wifiLabel;
extern lv_obj_t * ui_ipPanel;
extern lv_obj_t * ui_Image9;
extern lv_obj_t * ui_ipLabel;
extern lv_obj_t * ui_hotpotPanel;
extern lv_obj_t * ui_Image10;
extern lv_obj_t * ui_hotpotLabel;
extern lv_obj_t * ui_fresh_Label;
extern lv_obj_t * ui_settingPage;
extern lv_obj_t * ui_tempSetPanel;
extern lv_obj_t * ui_Label2;
void ui_event_tempSetSlider(lv_event_t * e);
extern lv_obj_t * ui_tempSetSlider;
extern lv_obj_t * ui_brightSetPanel;
extern lv_obj_t * ui_Label3;
void ui_event_brightSetSlider(lv_event_t * e);
extern lv_obj_t * ui_brightSetSlider;
extern lv_obj_t * ui_netSetPanel;
extern lv_obj_t * ui_Label6;
void ui_event_netSetBotton(lv_event_t * e);
extern lv_obj_t * ui_netSetBotton;
extern lv_obj_t * ui_fanSetPanel;
extern lv_obj_t * ui_Label4;
void ui_event_fanSetSlider(lv_event_t * e);
extern lv_obj_t * ui_fanSetSlider;
extern lv_obj_t * ui_aboutPage;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_temp_png);    // assets\temp.png
LV_IMG_DECLARE(ui_img_bright_png);    // assets\bright.png
LV_IMG_DECLARE(ui_img_wet_png);    // assets\wet.png
LV_IMG_DECLARE(ui_img_bomb_png);    // assets\bomb.png
LV_IMG_DECLARE(ui_img_fan_png);    // assets\fan.png
LV_IMG_DECLARE(ui_img_wifi_png);    // assets\WiFi.png
LV_IMG_DECLARE(ui_img_ip_png);    // assets\ip.png
LV_IMG_DECLARE(ui_img_hotpot_png);    // assets\hotpot.png

LV_FONT_DECLARE(ui_font_AlibabaPuHuiTi385Bold);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
