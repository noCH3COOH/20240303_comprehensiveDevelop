// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "gpio.h"
#include "web_server.h"

void LVGL_set_temp(lv_event_t * e)
{
	// Your code here
}

void LVGL_set_bright(lv_event_t * e)
{
	// Your code here
    extern GPIO_t led;
	led.set_pwm_duty(lv_slider_get_value(ui_brightSetSlider));
}

void LVGL_set_net(lv_event_t * e)
{
	// Your code here
    lv_label_set_text(ui_hotpotLabel, set_net_AP().c_str());
}

void LVGL_set_fan(lv_event_t * e)
{
	// Your code here
	extern GPIO_t fan;
	fan.set_pwm_duty(lv_slider_get_value(ui_fanSetSlider));
	lv_label_set_text(ui_fanLabel, (String(lv_slider_get_value(ui_fanSetSlider)) + "%").c_str());
}
