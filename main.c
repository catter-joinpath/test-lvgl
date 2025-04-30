#include <unistd.h>
#include <lvgl/lv_conf.h>
#include <lvgl/lvgl.h>
#include "ui/ui.h"

int main(int args, char **argv)
{
    lv_init();
    lv_display_t *display = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(display, "/dev/fb0");
    
    char *path = lv_libinput_find_dev(LV_LIBINPUT_CAPABILITY_TOUCH, true);
    lv_indev_t *indev = lv_libinput_create(LV_INDEV_TYPE_POINTER, path);
    lv_indev_set_display(indev, display);
    
    ui_init();
    while (1)
    {
        lv_task_handler();
        ui_tick();
        usleep(10000);
    }
    return 0;
}
