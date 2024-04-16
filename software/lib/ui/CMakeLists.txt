SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_temp_png.c
    images/ui_img_bright_png.c
    images/ui_img_wet_png.c
    images/ui_img_bomb_png.c
    images/ui_img_fan_png.c
    images/ui_img_wifi_png.c
    images/ui_img_ip_png.c
    images/ui_img_hotpot_png.c
    fonts/ui_font_AlibabaPuHuiTi385Bold.c)

add_library(ui ${SOURCES})
