#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO 22
#define BTN_GPIO 23
#define ESP_INTR_FLAG_DEFAULT 0

void IRAM_ATTR button_isr_handler(void *arg)
{
    gpio_intr_enable(BTN_GPIO);
    gpio_set_level(LED_GPIO, !gpio_get_level(LED_GPIO));
}
void app_main(void)
{
    gpio_pad_select_gpio(BTN_GPIO);
    gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(LED_GPIO, GPIO_MODE_INPUT_OUTPUT);
    gpio_pulldown_en(BTN_GPIO);
    gpio_set_intr_type(BTN_GPIO, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(BTN_GPIO, button_isr_handler, NULL);

    while (1)
    {
    }
}
