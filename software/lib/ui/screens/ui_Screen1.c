// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TabView1 = lv_tabview_create(ui_Screen1, LV_DIR_TOP, 50);
    lv_obj_set_width(ui_TabView1, lv_pct(100));
    lv_obj_set_height(ui_TabView1, lv_pct(100));
    lv_obj_set_align(ui_TabView1, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_TabView1, LV_STATE_DISABLED);       /// States
    lv_obj_clear_flag(ui_TabView1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_TabView1, lv_color_hex(0x292828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TabView1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(lv_tabview_get_tab_btns(ui_TabView1), &ui_font_AlibabaPuHuiTi385Bold,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_paraPage = lv_tabview_add_tab(ui_TabView1, "参数");

    ui_tempPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_tempPanel, lv_pct(30));
    lv_obj_set_height(ui_tempPanel, lv_pct(45));
    lv_obj_set_x(ui_tempPanel, lv_pct(-35));
    lv_obj_set_y(ui_tempPanel, lv_pct(-28));
    lv_obj_set_align(ui_tempPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_tempPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image1 = lv_img_create(ui_tempPanel);
    lv_img_set_src(ui_Image1, &ui_img_temp_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image1, lv_pct(0));
    lv_obj_set_y(ui_Image1, lv_pct(-20));
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image1, 80);

    ui_tempLabel = lv_label_create(ui_tempPanel);
    lv_obj_set_width(ui_tempLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_tempLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_tempLabel, lv_pct(0));
    lv_obj_set_y(ui_tempLabel, lv_pct(53));
    lv_obj_set_align(ui_tempLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_tempLabel, "0°C");

    ui_brightPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_brightPanel, lv_pct(30));
    lv_obj_set_height(ui_brightPanel, lv_pct(45));
    lv_obj_set_x(ui_brightPanel, lv_pct(0));
    lv_obj_set_y(ui_brightPanel, lv_pct(-28));
    lv_obj_set_align(ui_brightPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_brightPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image3 = lv_img_create(ui_brightPanel);
    lv_img_set_src(ui_Image3, &ui_img_bright_png);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image3, lv_pct(0));
    lv_obj_set_y(ui_Image3, lv_pct(-20));
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image3, 70);

    ui_brightLabel = lv_label_create(ui_brightPanel);
    lv_obj_set_width(ui_brightLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_brightLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_brightLabel, lv_pct(0));
    lv_obj_set_y(ui_brightLabel, lv_pct(53));
    lv_obj_set_align(ui_brightLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_brightLabel, "0px");

    ui_wetPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_wetPanel, lv_pct(30));
    lv_obj_set_height(ui_wetPanel, lv_pct(45));
    lv_obj_set_x(ui_wetPanel, lv_pct(35));
    lv_obj_set_y(ui_wetPanel, lv_pct(-28));
    lv_obj_set_align(ui_wetPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_wetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image4 = lv_img_create(ui_wetPanel);
    lv_img_set_src(ui_Image4, &ui_img_wet_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image4, lv_pct(0));
    lv_obj_set_y(ui_Image4, lv_pct(-20));
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image4, 80);

    ui_wetLabel = lv_label_create(ui_wetPanel);
    lv_obj_set_width(ui_wetLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_wetLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_wetLabel, lv_pct(0));
    lv_obj_set_y(ui_wetLabel, lv_pct(53));
    lv_obj_set_align(ui_wetLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wetLabel, "0");

    ui_bombPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_bombPanel, lv_pct(30));
    lv_obj_set_height(ui_bombPanel, lv_pct(45));
    lv_obj_set_x(ui_bombPanel, lv_pct(-35));
    lv_obj_set_y(ui_bombPanel, lv_pct(28));
    lv_obj_set_align(ui_bombPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_bombPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image5 = lv_img_create(ui_bombPanel);
    lv_img_set_src(ui_Image5, &ui_img_bomb_png);
    lv_obj_set_width(ui_Image5, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image5, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image5, lv_pct(0));
    lv_obj_set_y(ui_Image5, lv_pct(-20));
    lv_obj_set_align(ui_Image5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image5, 80);

    ui_bombLabel = lv_label_create(ui_bombPanel);
    lv_obj_set_width(ui_bombLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bombLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_bombLabel, lv_pct(0));
    lv_obj_set_y(ui_bombLabel, lv_pct(53));
    lv_obj_set_align(ui_bombLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_bombLabel, "0%");

    ui_fanPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_fanPanel, lv_pct(30));
    lv_obj_set_height(ui_fanPanel, lv_pct(45));
    lv_obj_set_x(ui_fanPanel, lv_pct(0));
    lv_obj_set_y(ui_fanPanel, lv_pct(28));
    lv_obj_set_align(ui_fanPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_fanPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image7 = lv_img_create(ui_fanPanel);
    lv_img_set_src(ui_Image7, &ui_img_fan_png);
    lv_obj_set_width(ui_Image7, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image7, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image7, lv_pct(0));
    lv_obj_set_y(ui_Image7, lv_pct(-20));
    lv_obj_set_align(ui_Image7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image7, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image7, 70);

    ui_fanLabel = lv_label_create(ui_fanPanel);
    lv_obj_set_width(ui_fanLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_fanLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_fanLabel, lv_pct(0));
    lv_obj_set_y(ui_fanLabel, lv_pct(53));
    lv_obj_set_align(ui_fanLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_fanLabel, "0%");

    ui_wifiPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_wifiPanel, lv_pct(30));
    lv_obj_set_height(ui_wifiPanel, lv_pct(45));
    lv_obj_set_x(ui_wifiPanel, lv_pct(-35));
    lv_obj_set_y(ui_wifiPanel, lv_pct(84));
    lv_obj_set_align(ui_wifiPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_wifiPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image8 = lv_img_create(ui_wifiPanel);
    lv_img_set_src(ui_Image8, &ui_img_wifi_png);
    lv_obj_set_width(ui_Image8, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image8, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image8, lv_pct(0));
    lv_obj_set_y(ui_Image8, lv_pct(-20));
    lv_obj_set_align(ui_Image8, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image8, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image8, 80);

    ui_wifiLabel = lv_label_create(ui_wifiPanel);
    lv_obj_set_width(ui_wifiLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_wifiLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_wifiLabel, lv_pct(0));
    lv_obj_set_y(ui_wifiLabel, lv_pct(53));
    lv_obj_set_align(ui_wifiLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_wifiLabel, "未连接");
    lv_obj_set_style_text_font(ui_wifiLabel, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ipPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_ipPanel, lv_pct(30));
    lv_obj_set_height(ui_ipPanel, lv_pct(45));
    lv_obj_set_x(ui_ipPanel, lv_pct(35));
    lv_obj_set_y(ui_ipPanel, lv_pct(28));
    lv_obj_set_align(ui_ipPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ipPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image9 = lv_img_create(ui_ipPanel);
    lv_img_set_src(ui_Image9, &ui_img_ip_png);
    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image9, lv_pct(0));
    lv_obj_set_y(ui_Image9, lv_pct(-20));
    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image9, 80);

    ui_ipLabel = lv_label_create(ui_ipPanel);
    lv_obj_set_width(ui_ipLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ipLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ipLabel, lv_pct(0));
    lv_obj_set_y(ui_ipLabel, lv_pct(53));
    lv_obj_set_align(ui_ipLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ipLabel, "-");

    ui_hotpotPanel = lv_obj_create(ui_paraPage);
    lv_obj_set_width(ui_hotpotPanel, lv_pct(30));
    lv_obj_set_height(ui_hotpotPanel, lv_pct(45));
    lv_obj_set_x(ui_hotpotPanel, lv_pct(0));
    lv_obj_set_y(ui_hotpotPanel, lv_pct(84));
    lv_obj_set_align(ui_hotpotPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_hotpotPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image10 = lv_img_create(ui_hotpotPanel);
    lv_img_set_src(ui_Image10, &ui_img_hotpot_png);
    lv_obj_set_width(ui_Image10, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_Image10, LV_SIZE_CONTENT);    /// 200
    lv_obj_set_x(ui_Image10, lv_pct(0));
    lv_obj_set_y(ui_Image10, lv_pct(-20));
    lv_obj_set_align(ui_Image10, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image10, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image10, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image10, 80);

    ui_hotpotLabel = lv_label_create(ui_hotpotPanel);
    lv_obj_set_width(ui_hotpotLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_hotpotLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_hotpotLabel, lv_pct(0));
    lv_obj_set_y(ui_hotpotLabel, lv_pct(53));
    lv_obj_set_align(ui_hotpotLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_hotpotLabel, "未配网");
    lv_obj_set_style_text_font(ui_hotpotLabel, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fresh_Label = lv_label_create(ui_paraPage);
    lv_obj_set_width(ui_fresh_Label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_fresh_Label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_fresh_Label, lv_pct(0));
    lv_obj_set_y(ui_fresh_Label, lv_pct(60));
    lv_obj_set_align(ui_fresh_Label, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_fresh_Label, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_settingPage = lv_tabview_add_tab(ui_TabView1, "设置");

    ui_tempSetPanel = lv_obj_create(ui_settingPage);
    lv_obj_set_width(ui_tempSetPanel, lv_pct(100));
    lv_obj_set_height(ui_tempSetPanel, lv_pct(15));
    lv_obj_set_x(ui_tempSetPanel, lv_pct(0));
    lv_obj_set_y(ui_tempSetPanel, lv_pct(-40));
    lv_obj_set_align(ui_tempSetPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_tempSetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label2 = lv_label_create(ui_tempSetPanel);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, lv_pct(-35));
    lv_obj_set_y(ui_Label2, lv_pct(0));
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "温度：30%");
    lv_obj_set_style_text_font(ui_Label2, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tempSetSlider = lv_slider_create(ui_tempSetPanel);
    lv_slider_set_value(ui_tempSetSlider, 30, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_tempSetSlider) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_tempSetSlider, 0,
                                                                                                  LV_ANIM_OFF);
    lv_obj_set_height(ui_tempSetSlider, 10);
    lv_obj_set_width(ui_tempSetSlider, lv_pct(65));
    lv_obj_set_x(ui_tempSetSlider, lv_pct(15));
    lv_obj_set_y(ui_tempSetSlider, lv_pct(0));
    lv_obj_set_align(ui_tempSetSlider, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_tempSetSlider, lv_color_hex(0x206DF0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tempSetSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_tempSetSlider, lv_color_hex(0xE119FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_tempSetSlider, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_tempSetSlider, lv_color_hex(0x5A5A5A), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tempSetSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_tempSetSlider, lv_color_hex(0x9E9E9E), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_tempSetSlider, LV_GRAD_DIR_VER, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_tempSetSlider, lv_color_hex(0x838383), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_tempSetSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_tempSetSlider, 1, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_tempSetSlider, 1, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_brightSetPanel = lv_obj_create(ui_settingPage);
    lv_obj_set_width(ui_brightSetPanel, lv_pct(100));
    lv_obj_set_height(ui_brightSetPanel, lv_pct(15));
    lv_obj_set_x(ui_brightSetPanel, lv_pct(0));
    lv_obj_set_y(ui_brightSetPanel, lv_pct(-20));
    lv_obj_set_align(ui_brightSetPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_brightSetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label3 = lv_label_create(ui_brightSetPanel);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, lv_pct(-35));
    lv_obj_set_y(ui_Label3, lv_pct(0));
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "亮度：30%");
    lv_obj_set_style_text_font(ui_Label3, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_brightSetSlider = lv_slider_create(ui_brightSetPanel);
    lv_slider_set_value(ui_brightSetSlider, 30, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_brightSetSlider) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_brightSetSlider, 0,
                                                                                                    LV_ANIM_OFF);
    lv_obj_set_height(ui_brightSetSlider, 10);
    lv_obj_set_width(ui_brightSetSlider, lv_pct(65));
    lv_obj_set_x(ui_brightSetSlider, lv_pct(15));
    lv_obj_set_y(ui_brightSetSlider, lv_pct(0));
    lv_obj_set_align(ui_brightSetSlider, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_brightSetSlider, lv_color_hex(0x206DF0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_brightSetSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_brightSetSlider, lv_color_hex(0xE119FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_brightSetSlider, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_brightSetSlider, lv_color_hex(0x5A5A5A), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_brightSetSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_brightSetSlider, lv_color_hex(0x9E9E9E), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_brightSetSlider, LV_GRAD_DIR_VER, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_brightSetSlider, lv_color_hex(0x838383), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_brightSetSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_brightSetSlider, 1, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_brightSetSlider, 1, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_netSetPanel = lv_obj_create(ui_settingPage);
    lv_obj_set_width(ui_netSetPanel, lv_pct(100));
    lv_obj_set_height(ui_netSetPanel, lv_pct(15));
    lv_obj_set_x(ui_netSetPanel, lv_pct(0));
    lv_obj_set_y(ui_netSetPanel, lv_pct(20));
    lv_obj_set_align(ui_netSetPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_netSetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_netSetPanel);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, lv_pct(-35));
    lv_obj_set_y(ui_Label6, lv_pct(0));
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "配网按钮");
    lv_obj_set_style_text_font(ui_Label6, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_netSetBotton = lv_btn_create(ui_netSetPanel);
    lv_obj_set_width(ui_netSetBotton, 80);
    lv_obj_set_height(ui_netSetBotton, 21);
    lv_obj_set_align(ui_netSetBotton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_netSetBotton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_netSetBotton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_netSetBotton, lv_color_hex(0x2650C9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_netSetBotton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_netSetBotton, lv_color_hex(0x222191), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_netSetBotton, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fanSetPanel = lv_obj_create(ui_settingPage);
    lv_obj_set_width(ui_fanSetPanel, lv_pct(100));
    lv_obj_set_height(ui_fanSetPanel, lv_pct(15));
    lv_obj_set_align(ui_fanSetPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_fanSetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label4 = lv_label_create(ui_fanSetPanel);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, lv_pct(-35));
    lv_obj_set_y(ui_Label4, lv_pct(0));
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "风扇效率：30%");
    lv_obj_set_style_text_font(ui_Label4, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fanSetSlider = lv_slider_create(ui_fanSetPanel);
    lv_slider_set_value(ui_fanSetSlider, 30, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_fanSetSlider) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_fanSetSlider, 0,
                                                                                                 LV_ANIM_OFF);
    lv_obj_set_height(ui_fanSetSlider, 10);
    lv_obj_set_width(ui_fanSetSlider, lv_pct(65));
    lv_obj_set_x(ui_fanSetSlider, lv_pct(15));
    lv_obj_set_y(ui_fanSetSlider, lv_pct(0));
    lv_obj_set_align(ui_fanSetSlider, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_fanSetSlider, lv_color_hex(0x206DF0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_fanSetSlider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_fanSetSlider, lv_color_hex(0xE119FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_fanSetSlider, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_fanSetSlider, lv_color_hex(0x5A5A5A), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_fanSetSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_fanSetSlider, lv_color_hex(0x9E9E9E), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_fanSetSlider, LV_GRAD_DIR_VER, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_fanSetSlider, lv_color_hex(0x838383), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_fanSetSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_fanSetSlider, 1, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_fanSetSlider, 1, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_aboutPage = lv_tabview_add_tab(ui_TabView1, "关于");

    ui_Label7 = lv_label_create(ui_aboutPage);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7,
                      "本产品由西安电子科技大学2024年课程\n综合开发实验第11小组开发完成");
    lv_obj_set_style_text_align(ui_Label7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &ui_font_AlibabaPuHuiTi385Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_tempSetSlider, ui_event_tempSetSlider, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_brightSetSlider, ui_event_brightSetSlider, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_netSetBotton, ui_event_netSetBotton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_fanSetSlider, ui_event_fanSetSlider, LV_EVENT_ALL, NULL);

}
