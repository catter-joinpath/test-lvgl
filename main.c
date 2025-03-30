#define LV_CONF_INCLUDE_SIMPLE
#define LV_USE_LINUX_FBDEV 1
#include <lvgl/lv_conf.h>
#include <lvgl/lvgl.h>
#include <lvgl/examples/lv_examples.h>

int main(int args, char **argv)
{
    lv_init();
    lv_display_t *display = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(display, "/dev/fb0");
    lv_example_get_started_1();

    while (1)
    {
        lv_task_handler();
        lv_delay_ms(5);
    }
    return 0;
}
