#include <stdio.h>
#include <unistd.h>
#include <lvgl/lv_conf.h>
#include <lvgl/lvgl.h>
#include "ui/ui.h"
#include "ui/screens.h"

#define FIRST_SCREEN SCREEN_ID_HEATING_SCREEN
#define LAST_SCREEN SCREEN_ID_LIGHTING_SCREEN

static void gesture_cb(lv_event_t * e)
{
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    int screen = eez_flow_get_current_screen();
    switch (dir) {
    case LV_DIR_TOP:
        printf("LV_DIR_TOP\n");
        screen = (screen - 1) >= FIRST_SCREEN ? (screen - 1) : LAST_SCREEN;
        eez_flow_set_screen(screen, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0);
        break;
    case LV_DIR_BOTTOM:
        printf("LV_DIR_BOTTOM\n");
        screen = (screen + 1) <= LAST_SCREEN ? (screen + 1) : FIRST_SCREEN;
        eez_flow_set_screen(screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0);
        break;
    default:
        printf("unsupported %d\n", dir);
        break;
    }
}

int main(int args, char **argv)
{
    lv_init();
    lv_display_t *display = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(display, "/dev/fb0");
    
    char *path = lv_libinput_find_dev(LV_LIBINPUT_CAPABILITY_TOUCH, true);
    lv_indev_t *indev = lv_libinput_create(LV_INDEV_TYPE_POINTER, path);
    lv_indev_set_display(indev, display);

    lv_indev_add_event_cb(indev, gesture_cb, LV_EVENT_GESTURE, NULL);
    
    ui_init();
    while (1)
    {
        lv_task_handler();
        ui_tick();
        usleep(10000);
    }
    return 0;
}
